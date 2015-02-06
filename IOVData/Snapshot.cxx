#ifndef IOVDATA_SNAPSHOT_CXX
#define IOVDATA_SNAPSHOT_CXX

#include "Snapshot.h"
#include "IOVDataError.h"
namespace lariov {

  template <class T>
  Snapshot<T>::Snapshot(std::string name)
  : _name(name)
  {}

  template <class T>
  const std::string& Snapshot<T>::Name () const { return _name;      }

  template <class T>
  const TTimeStamp&  Snapshot<T>::Start() const { return _iov_start; }

  template <class T>
  const TTimeStamp&  Snapshot<T>::End()   const { return _iov_end;   }

  template <class T>
  bool  Snapshot<T>::Valid(const TTimeStamp& ts) const 
  { return (_iov_start < ts && ts < _iov_end); }

  template <class T>
  size_t Snapshot<T>::NChannels() const { return _table.size();      }

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
  void Snapshot<T>::Reserve(size_t n)
  { _table.reserve(n); }

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
  void Snapshot<T>::Reset (const TTimeStamp& iov_start,
			   const TTimeStamp& iov_end,
			   const std::vector<std::string>& field_name,
			   const std::vector<std::string>& field_type)
  {
    if(iov_start >= iov_end)
      throw IOVDataError("IOV start cannot be larger than the end!");
    _iov_start = iov_start;
    _iov_end   = iov_end;
    if(field_name.size()!=field_type.size())
      throw IOVDataError("Name & Type column array has mis-match in length!");
    _field_name = field_name;

    size_t ctr=0;
    for(size_t i=0; i<_field_name.size(); ++i) {
      if(_field_name[i] == "channel") continue;
      _field_name_to_index[_field_name[i]] = ctr;
      ctr++;
    }

    _field_type.resize(field_type.size());
    
    for(size_t i=0; i<field_type.size(); ++i) {

      auto const& ft = field_type[i];
      ValueType_t vt(kUNKNOWN);
      if     ( ft == "smallint" || ft == "smallserial" ) vt = kSHORT;
      else if( ft == "integer"  || ft == "serial"      ) vt = kINT;
      else if( ft == "bigint"   || ft == "bigserial"   ) vt = kLONG;
      else if( ft == "real"                            ) vt = kFLOAT;
      else if( ft == "double precision"                ) vt = kDOUBLE;
      else if( ft == "text"                            ) vt = kSTRING;
      else {
	std::string msg("Unknown data type: ");
	msg += "\"" + ft + "\"";
	throw IOVDataError(msg.c_str());
      }
      _field_type[i] = vt;
    }
  }

}

#endif
