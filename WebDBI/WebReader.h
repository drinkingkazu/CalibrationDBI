/**
 * \file WebReader.h
 *
 * \ingroup WebInterface
 * 
 * \brief Class def header for a class WebReader
 *
 * @author kterao
 */

/** \addtogroup WebInterface

    @{*/
#ifndef WEBDB_WEBREADER_H
#define WEBDB_WEBREADER_H

#include "WebData.h"
#include "wda.h"
#include <map>
namespace webdb {

  /**
     \class WebReader
     User defined class WebReader ... these comments are used to generate
     doxygen documentation!
  */
  class WebReader{
    
  public:
    
    /// Default constructor
    WebReader(std::string  server  = "default",
	      std::string  port    = "default",
	      std::string  dbname  = "default",
	      unsigned int timeout = 0);
    
    /// Default destructor
    ~WebReader(){}

    const WebData& Request(const std::string& name,
			   const TTimeStamp&  ts);

    void Dump();

  private:
    std::string  _server;  ///< HTML server dns
    std::string  _port;    ///< Port ID
    std::string  _dbname;  ///< HTML server db name
    unsigned int _timeout; ///< Query timeout period [s]
    std::map<std::string, ::webdb::WebData> _data_m;
  };
}

#endif
/** @} */ // end of doxygen group 

