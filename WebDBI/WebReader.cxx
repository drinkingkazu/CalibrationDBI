#ifndef WEBDB_WEBREADER_CXX
#define WEBDB_WEBREADER_CXX

#include "WebReader.h"
#include "WebError.h"
#include <limits>
namespace webdb {
  
  WebReader::WebReader(std::string  server,
		       std::string  port,
		       std::string  dbname,
		       unsigned int timeout)
    : _timeout (timeout)
  {
    _server = (server != "default" ? server : getenv("LIBWDA_SERVER") );
    _port   = (port   != "default" ? port   : getenv("LIBWDA_PORT"  ) );
    _dbname = (dbname != "default" ? dbname : getenv("LIBWDA_DBNAME") );
  }

  const WebData& WebReader::Request(const std::string& name,
				    const TTimeStamp&  ts)
  {
    auto iter = _data_m.find(name);
    if(iter == _data_m.end()) {
      iter = (_data_m.emplace(std::make_pair(name,WebData(name)))).first;
    }
    if((*iter).second.Valid(ts)) return (*iter).second;
    
    std::string url("http://");
    url += _server;
    if(!_port.empty()) url += ":" + _port;
    url += "/" + _dbname + "/app";
    url += "/data?f=" + (*iter).second.Name();
    url += "&t=" + std::to_string(ts.GetSec()) + "." + std::to_string(int(ts.GetNanoSec()/1.e9));

    int err_code=0;
    auto data = getDataWithTimeout(url.c_str(),NULL,_timeout,&err_code);
    if(err_code) {
      std::cerr << "\033[93m" 
		<< __FUNCTION__
		<< "\033[00m" << std::endl
		<< "  Error code: " << err_code << std::endl
		<< "  Failed to execute a query: " << url.c_str() << std::endl
		<< "  Log: " << getHTTPmessage(data) << std::endl;
      releaseDataset(data);
      throw WebDataError("Failed to fetch WebData!");
    }

    TTimeStamp start, end;
    std::vector<std::string> str_array;
    std::vector<std::string> field_name;
    std::vector<std::string> field_type;
    char indefinite[30]="-";
    char buf[30];
    for(size_t row=0; row<(size_t)(getNtuples(data)); ++row) {
      auto tup = getTuple(data,row);
      if(row==0) {
	double t = getDoubleValue(tup,0,&err_code);
	if(err_code) {
	  releaseTuple(tup);
	  releaseDataset(data);
	  throw WebDataError("Failed to parse the IOV start time stamp!");
	}
	start.SetSec(int(t));
	start.SetNanoSec(int((t - start.GetSec())*1.e9));
      }
      else if(row==1) {

	int str_size = getStringValue(tup,0,buf,sizeof(buf),&err_code);
	if(err_code) {
	  releaseTuple(tup);
	  releaseDataset(data);
	  throw WebDataError("Failed to parse the IOV end time stamp!");
	}
	if(!(strncmp(buf,indefinite,str_size)))
	  end.SetSec(std::numeric_limits<int>::max());
	else{
	  double t = getDoubleValue(tup,0,&err_code);
	  if(err_code) {
	    releaseTuple(tup);
	    releaseDataset(data);
	    throw WebDataError("Failed to parse the IOV end time stamp!");
	  }
	  end.SetSec(int(t));
	  end.SetNanoSec(int((t - end.GetSec())*1.e9));	  
	}
      }
      else{
	str_array.resize(getNfields(tup),"");
	for(size_t column=0; column<(size_t)(getNfields(tup)); ++column) {
	  int str_size = getStringValue(tup,column,buf,sizeof(buf),&err_code);
	  if(err_code) {
	    releaseTuple(tup);
	    releaseDataset(data);
	    throw WebDataError("Failed to parse the table field names!");
	  }
	  str_array[column].assign(buf,str_size);
	}
      }
      if (!field_name.size()) 
	field_name = str_array;
      else if (!field_type.size()) {
	field_type = str_array;
	(*iter).second.Reset(start, end, field_name, field_type);
      }
      else
	(*iter).second.Append(str_array);
      releaseTuple(tup);
    }
    releaseDataset(data);
    return (*iter).second;
  }
  
  void WebReader::Dump() {
    const char* url = "http://dbdata0.fnal.gov:8086/uboonecon_dev/app/data?f=pedestals&t=12347578.000000";
    char buf[100];
    int err_code=0;
    auto data = getDataWithTimeout(url,
				   NULL,
				   10,
				   &err_code);
    
    std::cout << getNtuples(data) << std::endl;
    for(size_t i=0; i<(size_t)(getNtuples(data)); ++i) {
      auto tup = getTuple(data,i);
      for(size_t j=0; j<(size_t)(getNfields(tup)); ++j) {
	getStringValue(tup,j,buf,sizeof(buf),&err_code);
	std::cout<<"Row " << i << " Column "<<j<<" ... "<<buf<<std::endl;
      }
    }
  }

}

#endif
