/**
 * \file IOVDBError.h
 *
 * \ingroup IOVDB
 * 
 * \brief Collection of exception classes for IOVDB
 *
 * @author kterao
 */

/** \addtogroup IOVDB

    @{*/
#ifndef IOVDB_IOVDBERROR_H
#define IOVDB_IOVDBERROR_H

#include <iostream>
#include <exception>

namespace lariov {

  /**
     \class IOVDBError
  */
  class IOVDBError : public std::exception{

  public:

    IOVDBError(std::string msg="") : std::exception()
    {
      _msg = "\033[93m";
      _msg += msg;
      _msg += "\033[00m";
    }
    
    virtual ~IOVDBError() throw(){};
    virtual const char* what() const throw()
    { return _msg.c_str(); }

  private:
    std::string _msg;
  };

}

#endif
/** @} */ // end of doxygen group 

