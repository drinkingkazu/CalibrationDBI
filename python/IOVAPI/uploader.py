import inspect,logging,psycopg2
import os, sys, time
from db_utils import OpenDB, AskBinary
from pub_util import pub_logger, BaseException
from datetime import datetime

class tmp_data:
    
    def __init__(self):
        self._time = None
        self._name = ''
        self._field_name =[]
        self._field_type =[]
        self._table = {}

    def __repr__(self):
        msg = ''
        msg += '    Folder: ' + self._name + '\n'
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
        return self._name and self._time and len(self._field_name) == len(self._field_type) and len(self._field_name)

class ParserError(BaseException):

    def __init__(self):
        super(ParserError,self).__init__('Failed to parse input data file...')

class uploader(object):

    def __init__(self):
        self._logger = pub_logger.get_logger('pubdb')
        self._data = tmp_data()

    def _parse_folder(self,arg):
        if not len(arg):
            self._logger.error("Folder name not specified")
            raise ParserError()
        self._data._name = str(arg[0])
    def _parse_time(self,arg):
        if len(arg) < 2:
            self._logger.error("Not enough arguments to parse time information")
            raise ParserError()
        tstr = '%s %s' % (arg[0],arg[1])
        try:
            self._data._time = datetime.strptime(tstr,'%Y-%m-%d %H:%M:%S')
        except Exception:
            self._logger.error("Invalid time string expression: %s" % tstr)
            raise ParserError()
    def _parse_field_name(self,arg):
        self._data._field_name = tuple(arg)
    def _parse_field_type(self,arg):
        self._data._field_type = tuple(arg)

    def read(self,fname):
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
                    if cmd: cmd(words[1:len(words)])
                    if key == 'data_begin': 
                        data_region = True
                        if not self._data.valid():
                            self._logger.error('Invalid folder construction')
                            raise ParserError()
            elif key == 'data_end':
                data_region=False
            elif not (len(words)-1) == len(self._data._field_name):
                self._logger.error('Invalid data row (line %d)!' % line_num)
                raise ParserError()
            else:
                try:
                    ch = int(key)
                    if ch in self._data._table.keys():
                        self._logger.error('Duplicate channel (%d) entry (line %d)' % (ch,line_num))
                        raise ParserError()
                    self._data._table[ch]=tuple(words[1:len(words)])

                except ValueError:
                    self._logger.error('Invalid channel specification string (\"%s\") (line %d)' % (key,line_num))
                    raise ParserError()
        if data_region:
            self._logger.error('Rerached EOF but did not find data_end specification')
            raise ParserError()
        return True

    def upload(self):
        if not self._data.valid():
            self._logger.error('No data to upload...')
            return False
        self._logger.warning(' Loaded data definitions shown below.')
        print self._data
        print
        if not AskBinary('Proceed?'): return False

        db=OpenDB()
        folders = db.getFolders()
        folder = None
        if self._data._name in folders:
            folder = db.openFolder(self._data._name)
            self._logger.warning('  Folder \"%s\" already exists with following IOVs.' % self._data._name)
            
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
            if not AskBinary('Folder \"%s\" does not exist yet. Create?' % self._data._name):
                db.disconnect()
                return False
            defs = []
            for x in xrange(len(self._data._field_type)):
                defs.append((self._data._field_name[x],self._data._field_type[x]))
            print defs
            folder = db.createFolder(self._data._name,defs)

        if not AskBinary('Really upload this to the death star?'):
            db.disconnect()
            return False
        t0=time.time()
        try:
            self._logger.warning('Attempting to upload data...')
            folder.addData(self._data._time,self._data._table)
        except psycopg2.ProgrammingError:
            self._logger.error('Failed add data to the folder!')
            db.disconnect()
            raise
        self._logger.warning('Data uploaded (time taken %g [s])' % (time.time()-t0))
        return True

