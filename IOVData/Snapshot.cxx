#ifndef IOVDATA_SNAPSHOT_CXX
#define IOVDATA_SNAPSHOT_CXX

#include "Snapshot.h"
#include "IOVDataError.h"
namespace lariov {
  
  Snapshot::Snapshot(std::string name) : _name(name)
  {}

  const std::string& Snapshot::Name () const { return _name;      }
  const TTimeStamp&  Snapshot::Start() const { return _iov_start; }
  const TTimeStamp&  Snapshot::End()   const { return _iov_end;   }
  
  bool  Snapshot::Valid(const TTimeStamp& ts) const 
  { return (_iov_start < ts && ts < _iov_end); }

  size_t Snapshot::NChannels() const { return _table.size();      }
  size_t Snapshot::NFields()   const { return _field_name.size(); }

  const std::string& Snapshot::FieldName(const size_t& column) const
  {
    if(column >= _field_name.size()) 
      throw IOVDataError("Invalid column number requested!");
    return _field_name[column];
  }

  ValueType_t Snapshot::FieldType(const size_t& column) const
  {
    if(column >= _field_type.size())
      throw IOVDataError("Invalid column number requested!");
    return _field_type[column];
  }

  const std::vector<ValueType_t>& Snapshot::FieldType() const { return _field_type; }
  const std::vector<std::string>& Snapshot::FieldName() const { return _field_name; }

  void Snapshot::Reserve(size_t n)
  { _table.reserve(n); }

  void Snapshot::Reset (const TTimeStamp& iov_start,
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
	msg += ft;
	throw IOVDataError(msg.c_str());
      }
      _field_type[i] = vt;
    }
  }

}

#endif