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
#ifndef CALIBDB_WEBREADER_H
#define CALIBDB_WEBREADER_H

#include <iostream>
#include "wda.h"

namespace calibdb {
  /**
     \class WebReader
     User defined class WebReader ... these comments are used to generate
     doxygen documentation!
  */
  class WebReader{
    
  public:
    
    /// Default constructor
    WebReader(){}
    
    /// Default destructor
    ~WebReader(){}
    
    void Dump() {
      const char* url = "http://dbdata0.fnal.gov:8086/uboonecon_dev/app/data?f=pedestals&t=12347578.000000";
      char buf[100];
      int err_code=0;
      auto data = getDataWithTimeout(url,
				     NULL,
				     10,
				     &err_code);
      
      std::cout << getNtuples(data) << std::endl;
      for(size_t i=0; i<getNtuples(data); ++i) {
	auto tup = getTuple(data,i);
	for(size_t j=0; j<getNfields(tup); ++j) {
	  int str_size = getStringValue(tup,j,buf,sizeof(buf),&err_code);
	  std::cout<<"Row " << i << " Column "<<j<<" ... "<<buf<<std::endl;
	}
      }
    }
    
  private:
    
    
  };
}

#endif
/** @} */ // end of doxygen group 

