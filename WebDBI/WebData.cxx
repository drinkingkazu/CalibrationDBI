#ifndef WEBDB_WEBDATA_CXX
#define WEBDB_WEBDATA_CXX

#include "WebData.h"
#include "WebError.h"
namespace webdb {
  
  WebData::WebData(std::string name) : _name(name)
  {}

  const std::string& WebData::Name () const { return _name;      }
  const TTimeStamp&  WebData::Start() const { return _iov_start; }
  const TTimeStamp&  WebData::End()   const { return _iov_end;   }
  
  bool  WebData::Valid(const TTimeStamp& ts) const 
  { return (_iov_start < ts && ts < _iov_end); }

  size_t WebData::NRows()    const { return _table.size();      }
  size_t WebData::NColumns() const { return _field_name.size(); }

  const std::string& WebData::FieldName(const size_t& column) const
  {
    if(column >= _field_name.size()) 
      throw WebDataError("Invalid column number requested!");
    return _field_name[column];
  }

  ValueType_t WebData::FieldType(const size_t& column) const
  {
    if(column >= _field_type.size())
      throw WebDataError("Invalid column number requested!");
    return _field_type[column];
  }

  const std::vector<ValueType_t>& WebData::FieldType() const { return _field_type; }
  const std::vector<std::string>& WebData::FieldName() const { return _field_name; }

  const Row_t& WebData::Row(const size_t n) const
  {
    if(n >= _table.size())
      throw WebDataError("Invalid row number requested!");
    return _table[n];
  }

  const std::string& WebData::Field(const size_t& row, 
				    const size_t& column) const
  {
    if(column >= _field_type.size())
      throw WebDataError("Invalid column number requested!");
    return Row(row)[column];
  }

  void WebData::Reserve(size_t n)
  { _table.reserve(n); }

  void WebData::Append(const Row_t& row)
  {
    if(row.size() != _field_type.size())
      throw WebDataError("Invalid number of columns in the new row!");
    _table.push_back(row);
  }

  void WebData::Reset (const TTimeStamp& iov_start,
		       const TTimeStamp& iov_end,
		       const std::vector<std::string>& field_name,
		       const std::vector<std::string>& field_type)
  {
    if(iov_start >= iov_end)
      throw WebDataError("IOV start cannot be larger than the end!");
    _iov_start = iov_start;
    _iov_end   = iov_end;
    if(field_name.size()!=field_type.size())
      throw WebDataError("Name & Type column array has mis-match in length!");
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
	throw WebDataError(msg.c_str());
      }
      _field_type[i] = vt;
    }
  }

}

#endif
