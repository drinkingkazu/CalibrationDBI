/**
 * \file Snapshot.h
 *
 * \ingroup IOVDB
 * 
 * \brief Class def header for a class Snapshot
 *
 * @author kterao
 */

/** \addtogroup IOVDB

    @{*/
#ifndef IOVDB_WEBDATA_H
#define IOVDB_WEBDATA_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <TTimeStamp.h>
#include <TObject.h>
#include "IOVDBError.h"
#include "IOVDBConstants.h"
#include "TableDef.h"
namespace lariov {

  template <class T>
  class WebReader;

  /**
     \class Snapshot
  */
  template <class T>
  class Snapshot : public TObject
  {
		   
    friend class WebReader<T>;
  public:
    
    /// Default constructor
    Snapshot(std::string folder="noname" );
    
    /// Default destructor
    virtual ~Snapshot(){}

    void clear();
    void reserve(size_t n);

    const std::string& Folder() const;
    const TTimeStamp&  Start() const;
    const TTimeStamp&  End()   const;
    const std::string& Tag() const;

    bool   Valid(const TTimeStamp& ts) const;

    size_t NChannels()    const;

    const std::vector<T>& ChData() const;

    const lariov::TableDef TableDef() const;

    bool Compat(const Snapshot<T>& data) const;
    
    void Reset(const TTimeStamp start = ::lariov::kMIN_TIME);

  private:
    
    void Reset(const TTimeStamp& start, const TTimeStamp& end, const std::string tag="");
    
    //
    // Template functions
    //
  public:

    const T& Row(const size_t n) const
    {
      if(n >= _data.size())
	throw IOVDBError("Invalid row number requested!");
      return _data[n];
    }

    const T& ChData(const unsigned int ch) const
    {
      auto iter = std::lower_bound (_data.begin(), _data.end(), ch);
      if(iter == _data.end()){
	std::string msg("Channel not found: ");
	msg += std::to_string(ch);
	throw IOVDBError(msg);
      }
      return (*iter);
    }

    inline void Append(const T& data)
    {

      auto const iter = std::lower_bound(_data.begin(), _data.end(), data);

      if(iter != _data.end()) throw IOVDBError("Cannot insert a duplicate channel!");

      bool sort = (_data.size() && data < _data.back());
      
      _data.push_back(data);

      if(sort) std::sort(_data.begin(),_data.end());

    }

  private:
    std::vector<T> _data;
    std::string _folder;
    TTimeStamp  _iov_start;
    TTimeStamp  _iov_end;
    std::string _tag;

    ClassDef(Snapshot,1)
  };
}

#endif
/** @} */ // end of doxygen group 

