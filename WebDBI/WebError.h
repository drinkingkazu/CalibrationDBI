/**
 * \file WebError.h
 *
 * \ingroup WebInterface
 * 
 * \brief Collection of exception classes for WebInterface
 *
 * @author kterao
 */

/** \addtogroup WebInterface

    @{*/
#ifndef WEBDB_WEBERROR_H
#define WEBDB_WEBERROR_H

#include <iostream>
#include <exception>

namespace webdb {

  /**
     \class WebDataError
  */
  class WebDataError : public std::exception{

  public:

    WebDataError(std::string msg="") : std::exception()
    {
      _msg = "\033[93m";
      _msg += msg;
      _msg += "\033[00m";
    }
    
    virtual ~WebDataError() throw(){};
    virtual const char* what() const throw()
    { return _msg.c_str(); }

  private:
    std::string _msg;
  };

}

#endif
/** @} */ // end of doxygen group 

