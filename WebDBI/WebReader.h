/**
 * \file WebReader.h
 *
 * \ingroup WebDBI
 * 
 * \brief Class def header for a class WebReader
 *
 * @author kterao
 */

/** \addtogroup WebDBI

    @{*/
#ifndef WEBDBI_WEBREADER_H
#define WEBDBI_WEBREADER_H

#include "IOVDB/Snapshot.h"
#include "WDAConnInfo.h"
#include <map>
namespace lariov {

  /**
     \class WebReader
     User defined class WebReader ... these comments are used to generate
     doxygen documentation!
  */
  template <class T>
  class WebReader{

  private:
    /// Default ctor
    WebReader();

    /// Alternative ctor
    WebReader(const WDAConnInfo& conn_info);
    
    /// Default destructor
    ~WebReader(){}

    /// Connection info updater
    void SetConnInfo(const WDAConnInfo& conn);

  public:

    /// Singleton getter
    static WebReader<T>& GetME() {
      if(!_me) _me = new WebReader<T>();
      return *_me;
    }

    static WebReader<T>& GetME(const WDAConnInfo& conn) {
      if(!_me) _me = new WebReader<T>(conn);
      else _me->SetConnInfo(conn);
      return *_me;
    }

    static WebReader<T>& GetME(const std::string& server,
			       const std::string& port,
			       const std::string& dbname,
			       const unsigned int timeout=kDEFAULT_WDA_TIMEOUT_SEC)
    {
      WDAConnInfo conn(server,port,dbname,timeout);
      return GetME(conn);
    }

    /// Single useful function to load DB contents
    const Snapshot<T>& Request(const std::string& name,
			       const TTimeStamp&  ts,
			       const std::string  tag="");
    
  private:
    static WebReader<T>* _me;
    WDAConnInfo _conn;   ///< Connection information
    std::map<std::string, lariov::Snapshot<T> > _data_m;

  };
}

template <class T>
lariov::WebReader<T>* lariov::WebReader<T>::_me = nullptr;

#endif
/** @} */ // end of doxygen group 

