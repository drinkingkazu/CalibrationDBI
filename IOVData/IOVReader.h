/**
 * \file IOVReader.h
 *
 * \ingroup WebDBI
 * 
 * \brief Class def header for a class IOVReader
 *
 * @author kterao
 */

/** \addtogroup WebDBI

    @{*/
#ifndef IOVDATA_IOVREADER_H
#define IOVDATA_IOVREADER_H

#include "Snapshot.h"
#include "wda.h"
#include <map>
namespace lariov {

  /**
     \class IOVReader
     User defined class IOVReader ... these comments are used to generate
     doxygen documentation!
  */
  template <class T>
  class IOVReader{
    
  public:
    
    /// Default constructor
    IOVReader(std::string  server  = "default",
	      std::string  port    = "default",
	      std::string  dbname  = "default",
	      unsigned int timeout = 0);
    
    /// Default destructor
    ~IOVReader(){}

    const Snapshot<T>& Request(const std::string& name,
			       const TTimeStamp&  ts);
    
  private:

    std::string  _server;  ///< HTML server dns
    std::string  _port;    ///< Port ID
    std::string  _dbname;  ///< HTML server db name
    unsigned int _timeout; ///< Query timeout period [s]
    std::map<std::string, ::lariov::Snapshot<T> > _data_m;

  };
}

template class lariov::IOVReader<std::string>;
#endif
/** @} */ // end of doxygen group 

