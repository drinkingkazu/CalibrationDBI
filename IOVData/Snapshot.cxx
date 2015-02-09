#ifndef IOVDATA_SNAPSHOT_CXX
#define IOVDATA_SNAPSHOT_CXX

#include "Snapshot.h"
#include "UtilFunc.h"
#include "IOVDataError.h"

namespace lariov {

  template <class T>
  Snapshot<T>::Snapshot(std::string folder)
    : _folder(folder)
  {this->clear();}

  template <class T>
  Snapshot<T>::Snapshot(const std::string& folder,
			const std::vector<std::string>& field_name,
			const std::vector<std::string>& field_type)
    : Snapshot(folder,field_name,::lariov::Str2ValueType(field_type))
  {}

  template <class T>
  Snapshot<T>::Snapshot(const std::string& folder,
			const std::vector<std::string>& field_name,
			const std::vector< ::lariov::ValueType_t>& field_type)
    : _folder(folder)
    , _field_name(field_name)
    , _field_type(field_type)
  {

    if(field_name.size()!=field_type.size())
      throw IOVDataError("Name & Type column array has mis-match in length!");

    size_t ctr=0;
    for(size_t i=0; i<_field_name.size(); ++i) {
      if(_field_name[i] == "channel") continue;
      if(_field_name_to_index.find(_field_name[i]) != _field_name_to_index.end())
	throw IOVDataError("Duplicate name used!");
      _field_name_to_index[_field_name[i]] = ctr;
      ctr++;
    }
  }

  template <class T>
  void Snapshot<T>::clear()
  { 
    std::vector<lariov::ChData<T> >::clear();
    _iov_start = kMAX_TIME;
    _iov_end = kMAX_TIME;
  }

  template <class T>
  const std::string& Snapshot<T>::Folder () const { return _folder;      }

  template <class T>
  const TTimeStamp&  Snapshot<T>::Start() const { return _iov_start; }

  template <class T>
  const TTimeStamp&  Snapshot<T>::End()   const { return _iov_end;   }

  template <class T>
  bool  Snapshot<T>::Valid(const TTimeStamp& ts) const 
  { return (_iov_start < ts && ts < _iov_end); }

  template <class T>
  size_t Snapshot<T>::NChannels() const { return this->size();      }

  template <class T>
  size_t Snapshot<T>::NFields()   const { return _field_name.size(); }

  template <class T>
  const std::string& Snapshot<T>::FieldName(const size_t column) const
  {
    if(column >= _field_name.size()) 
      throw IOVDataError("Invalid column number requested!");
    return _field_name[column];
  }

  template <class T>
  ValueType_t Snapshot<T>::FieldType(const size_t column) const
  {
    if(column >= _field_type.size())
      throw IOVDataError("Invalid column number requested!");
    return _field_type[column];
  }

  template <class T>
  const std::vector<ValueType_t>& Snapshot<T>::FieldType() const { return _field_type; }

  template <class T>
  const std::vector<std::string>& Snapshot<T>::FieldName() const { return _field_name; }

  template <class T>
  size_t Snapshot<T>::Name2Index(const std::string& field_name) const
  {
    auto const& iter = _field_name_to_index.find(field_name);
    if(iter == _field_name_to_index.end()) {
      std::string msg("Field not found" + field_name);
      throw IOVDataError(msg.c_str());
    }
    return (*iter).second;
  }

  template <class T>
  bool Snapshot<T>::Compat(const std::vector<std::string>& field_name,
			   const std::vector<std::string>& field_type) const
  { return Compat(field_name,Str2ValueType(field_type)); }

  template <class T>
  bool Snapshot<T>::Compat(const std::vector<std::string>& field_name,
			   const std::vector< ::lariov::ValueType_t> field_type) const
  {
    if(FieldName().size() != field_name.size() ||
       FieldType().size() != field_type.size() ) return false;
    
    for(size_t i=0; i<this->FieldName().size(); ++i) {
      
      auto const& name1 = this->FieldName()[i];
      auto const& name2 = field_name[i];
      auto const& type1 = this->FieldType()[i];
      auto const& type2 = field_type[i];
      
      if(name1 != name2 || type1 != type2)
	return false;
    }
    return true;
  }

  template <class T>
  void Snapshot<T>::Reset (const TTimeStamp iov_start,
			   const TTimeStamp iov_end)
  {
    if(iov_start >= iov_end)
      throw IOVDataError("IOV start cannot be larger than the end!");
    this->clear();
    _iov_start = iov_start;
    _iov_end   = iov_end;
  }
  //  ClassImp(Snapshot)  
}

#endif
