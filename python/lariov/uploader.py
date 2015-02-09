import inspect,logging,psycopg2
import os, sys, time
from ROOT import TFile, TTimeStamp, std
from db_utils import AskBinary, OpenDB
from ROOT import lariov
from pub_util import pub_logger, BaseException
from datetime import datetime

class parsed_data:
    
    def __init__(self):
        self._time = None
        self._folder = ''
        self._field_name =[]
        self._field_type =[]
        self._table = {}

    def __repr__(self):
        msg = ''
        msg += '    Folder: ' + self._folder + '\n'
        msg += '    Time  : ' + str(self._time) + '\n'
        msg += '    Field Names: ' 
        for x in self._field_name: msg += str(x) + ' '
        msg += '\n'
        msg += '    Field Types: '
        for x in self._field_type: msg += str(x) + ' '
        msg += '\n'
        msg += '  %d channel entries...' % len(self._table)
        msg += '\n'
        return msg

    def valid(self):
        return self._folder and self._time and len(self._field_name) == len(self._field_type) and len(self._field_name)

class ParserError(BaseException):

    def __init__(self):
        super(ParserError,self).__init__('Failed to parse input data file...')

class IOVDataUploader(object):

    def __init__(self):
        self._logger = pub_logger.get_logger('pubdb')
        self._data = None

    def _parse_folder(self,data,arg):
        if not len(arg):
            self._logger.error("Folder name not specified")
            raise ParserError()
        data._folder = str(arg[0])

    def _parse_time(self,data,arg):
        if len(arg) < 2:
            self._logger.error("Not enough arguments to parse time information")
            raise ParserError()
        tstr = ''
        if len(arg) == 2:
            tstr = '%s %s 000000' % (arg[0],arg[1])
        else:
            tstr = '%s %s %06d' % (arg[0],arg[1],int(arg[2]))
        try:
            ts = datetime.strptime(tstr,'%Y-%m-%d %H:%M:%S %f')
            data._time = TTimeStamp(ts.year, ts.month, ts.day, ts.hour, ts.minute, ts.second, ts.microsecond*1000)
        except Exception:
            self._logger.error("Invalid time string expression: %s" % tstr)
            raise ParserError()
    def _parse_field_name(self,data,arg):
        data._field_name = tuple(arg)
    def _parse_field_type(self,data,arg):
        data._field_type = tuple(arg)

    def add(self,fname,folder=""):

        if fname.endswith('.root'): return _read_rootfile(fname,folder)
        else: return self._read_txtfile(fname)

    def _read_rootfile(self,fname,folder):
        
        if not os.path.isfile(fname):
            self._logger.error("File does not exist %s" % fname)
            return False

        fin = TFile.Open(fname,"READ")
        if not fin:
            self._logger.error("Failed to open a TFile %s" % fname)
            return False

        ss_col = lariov.SnapshotCollection("string")(folder)

        ss_col.Read(fin)

        if not self._data:
            self._data = ss_col
        else:
            self._data.Merge(ss_col)

        return True

    def _read_txtfile(self,fname):

        data = parsed_data()

        content=''
        try:
            content = open(fname,'r').read()
        except IOError:
            self._logger.error("Failed to open a file: %s" % fname)
            return False

        commands = {'folder' : self._parse_folder,
                    'time'   : self._parse_time,
                    'field'  : self._parse_field_name,
                    'type'   : self._parse_field_type,
                    'data_begin' : None }
        command_keys=commands.keys()

        data_region=False
        content = content.split('\n')
        for line_num in xrange(len(content)):
            line = content[line_num]
            if line.find('#') >=0:
                line = line[0:line.find('#')]
            words = line.split()
            if not words: continue
            key=words[0].lower()
            if not data_region:
                if not key in command_keys:
                    self._logger.error('Failed to parse line %d: %s' % (line_num,line))
                    raise ParserError()
                else:
                    cmd = commands[key.lower()]
                    if cmd: cmd(data,words[1:len(words)])
                    if key == 'data_begin': 
                        data_region = True
                        if not data.valid():
                            self._logger.error('Invalid folder construction')
                            raise ParserError()

            elif key == 'data_end':
                data_region=False
            elif not (len(words)-1) == len(data._field_name):
                self._logger.error('Invalid data row (line %d)!' % line_num)
                raise ParserError()
            else:
                try:
                    ch = int(key)
                    if ch in data._table.keys():
                        self._logger.error('Duplicate channel (%d) entry (line %d)' % (ch,line_num))
                        raise ParserError()
                    data._table[ch]=tuple(words[1:len(words)])

                except ValueError:
                    self._logger.error('Invalid channel specification string (\"%s\") (line %d)' % (key,line_num))
                    raise ParserError()
        if data_region:
            self._logger.error('Rerached EOF but did not find data_end specification')
            raise ParserError()

        if not data.valid():
            self._logger.error('Parsed data contents does not form a valid Snapshot. See below.')
            print data
            return False

        if not self._data:
            self._data = lariov.SnapshotCollection("string")(data._folder)

        field_name = std.vector("string")(len(data._field_name),"")
        field_type = std.vector("string")(len(data._field_type),"")
        for x in xrange(len(data._field_name)):
            field_name[x] = data._field_name[x]
        for x in xrange(len(data._field_type)):
            field_type[x] = data._field_type[x]
        ss_data = lariov.Snapshot("string")(data._folder,
                                            field_name,
                                            field_type)
        ss_data.Reset(data._time)
        for ch in data._table.keys():
            row = data._table[ch]
            ch_data = lariov.ChData("string")()
            ch_data.Channel(ch)
            ch_data.reserve(len(row))
            for v in row:
                ch_data.push_back(v)
            ss_data.push_back(ch_data)
        self._data.Append(ss_data)
        
        return True

    def upload(self):
        if not self._data:
            self._logger.error("No data to upload")
            return False

        db=OpenDB()
        folders = db.getFolders()
        folder = None
        if self._data.Folder() in folders:
            folder = db.openFolder(self._data.Folder())
            self._logger.warning('  Folder \"%s\" already exists with following IOVs.' % self._data.Folder())
            
            iovs = folder.getIOVs(0,2047570047)
            for x in xrange(len(iovs)):
                if x < (len(iovs)-1):
                    print '    IOV id %d : %s => %s' % (iovs[x][0],iovs[x][1],iovs[x+1][1])
                else:
                    print '    IOV id %d : %s => future' % (iovs[x][0],iovs[x][1])
            print
            if not AskBinary('Proceed?'):
                db.disconnect()
                return False

        else:
            if not AskBinary('Folder \"%s\" does not exist yet. Create?' % self._data.Folder()):
                db.disconnect()
                return False
            defs = []
            for x in xrange(len(self._data._field_type)):
                defs.append((self._data.SnapshotArray()[x].FieldName(x),self._data.SnapshotArray()[x].FieldTypeString(x)))
            print defs
            folder = db.createFolder(self._data.Folder(),
                                     defs,
                                     grants={'kterao'     : 'rw',
                                             'andrzejs'   : 'rw',
                                             'uboone_web' : 'r'
                                             }
                                     )

        if not AskBinary('Really upload this to the death star?'):
            db.disconnect()
            return False
        try:
            num_ss = self._data.SnapshotArray().size()
            self._logger.warning('Attempting to upload %d Snapshot(s)...' % num_ss)
            for x in xrange(num_ss):
                t0=time.time()
                table = {}
                ss = self._data.SnapshotArray()[x]
                ts = ss.Start()
                for y in xrange(ss.size()):
                    ch_data = ss.Data(y)
                    values = []
                    for z in xrange(ch_data.size()):
                        values.append(str(ch_data[z]))
                    table[ch_data.Channel()] = tuple(values)
                py_ts = datetime.strptime("%s %06d" % (ss.Start().AsString("s"),
                                                       int(ss.Start().GetNanoSec()/1.e3)),
                                          '%Y-%m-%d %H:%M:%S %f')
                folder.addData(py_ts,table)
                self._logger.warning('Done uploading Snapshot %d/%d ... %g [s]' % (x,num_ss,time.time()-t0))
        except psycopg2.ProgrammingError:
            self._logger.error('Failed add data to the folder!')
            db.disconnect()
            raise
        return True

