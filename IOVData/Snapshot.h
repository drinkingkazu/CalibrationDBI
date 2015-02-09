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
#include <TObject.h>
#include "ChData.h"
#include "IOVDataError.h"
#include "IOVDataConstants.h"
namespace lariov {

  template <class T>
  class WebReader;

  /**
     \class Snapshot
  */
  template <class T>
  class Snapshot : public std::vector< lariov::ChData<T> > 
#ifndef CALIBDB_LOCAL_BUILD
		 , public TObject
#endif
  {
		   
    friend class WebReader<T>;
  public:
    
    /// Default constructor
    Snapshot(std::string folder="noname" );
    
    /// Default destructor
    virtual ~Snapshot(){}

    /// Alternative ctor ... for creating Snapshot to be uploaded
    Snapshot(const std::string& folder,
	     const std::vector<std::string>& field_name,
	     const std::vector<std::string>& field_type);

    Snapshot(const std::string& name,
	     const std::vector<std::string>& field_name,
	     const std::vector< ::lariov::ValueType_t>& field_type);

    void clear();

    const std::string& Folder() const;
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

    bool Compat(const std::vector<std::string>& field_name,
		const std::vector<std::string>& field_type) const;

    bool Compat(const std::vector<std::string>& field_name,
		const std::vector< ::lariov::ValueType_t> field_type) const;

    void Reset(const TTimeStamp start = ::lariov::kMIN_TIME,
	       const TTimeStamp end   = ::lariov::kMAX_TIME);
    
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

      if(!(_field_type.size())) throw IOVDataError("Not configured yet toadd ChData!!");

      if(data.size() != (_field_type.size()-1))
	throw IOVDataError("Invalid number of columns in the new row!");

      bool sort = (this->size() && data < this->back());

      std::vector<lariov::ChData<T> >::push_back(data);

      if(sort) std::sort(this->begin(),this->end());

    }

  private:

  std::string _folder;
    TTimeStamp  _iov_start;
    TTimeStamp  _iov_end;
    std::vector<std::string> _field_name;
    std::vector<lariov::ValueType_t> _field_type;
    std::map<std::string,size_t> _field_name_to_index;

#ifndef CALIBDB_LOCAL_BUILD
    ClassDef(Snapshot,1)
#endif
  };
}

template class lariov::Snapshot<std::string>;

#endif
/** @} */ // end of doxygen group 

