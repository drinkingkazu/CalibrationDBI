/**
 * \file Snapshot.h
 *
 * \ingroup Snapshot
 * 
 * \brief Class def header for a class Snapshot
 *
 * @author kterao
 */

/** \addtogroup Snapshot

    @{*/
#ifndef WEBDB_WEBDATA_H
#define WEBDB_WEBDATA_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <TTimeStamp.h>
#include "ChData.h"
#include "IOVDataError.h"

namespace lariov {

  template <class T>
  class WebReader;

  enum ValueType_t {
    kSTRING,
    kSHORT,
    kINT,
    kLONG,
    kFLOAT,
    kDOUBLE,
    kTIMESTAMP,
    kUNKNOWN
  };

  /**
     \class Snapshot
  */
  template <class T>
  class Snapshot : public std::vector< lariov::ChData<T> > {
    friend class WebReader<T>;
  public:
    
    /// Default constructor
    Snapshot(std::string name="noname" );
    
    /// Default destructor
    ~Snapshot(){}

    void clear();

    const std::string& Name() const;
    const TTimeStamp&  Start() const;
    const TTimeStamp&  End()   const;

    bool   Valid(const TTimeStamp& ts) const;
    size_t NChannels()    const;
    size_t NFields() const;

    const std::string& FieldName(const size_t column) const;
    ValueType_t        FieldType(const size_t column) const;
    const std::vector<lariov::ValueType_t>& FieldType() const;
    const std::vector<std::string>& FieldName() const;
    size_t Name2Index(const std::string& field_name) const;

  private:

    void Reset (const TTimeStamp& iov_start,
		const TTimeStamp& iov_end,
		const std::vector<std::string>& field_name,
		const std::vector<std::string>& field_type);

    //
    // Template functions
    //
  public:
    const lariov::ChData<T>& Data(const size_t n) const
    {
      if(n >= this->size())
	throw IOVDataError("Invalid row number requested!");
      return (*this)[n];
    }

    inline void push_back(const lariov::ChData<T>& data)
    {

      bool sort = (this->size() && data < this->back());

      std::vector<lariov::ChData<T> >::push_back(data);

      if(sort) std::sort(this->begin(),this->end());

    }

  private:
    void Append  (const lariov::ChData<T>& row)
    {
      if(!(_field_type.size())) throw IOVDataError("Not configured yet to call Snapshot::Append()!");
      if(row.size() != (_field_type.size()-1))
	throw IOVDataError("Invalid number of columns in the new row!");
      this->push_back(row);
    }

  private:

    std::string _name;
    TTimeStamp  _iov_start;
    TTimeStamp  _iov_end;
    std::vector<std::string> _field_name;
    std::vector<lariov::ValueType_t> _field_type;
    std::map<std::string,size_t> _field_name_to_index;
  };
}

template class lariov::Snapshot<std::string>;

#endif
/** @} */ // end of doxygen group 

