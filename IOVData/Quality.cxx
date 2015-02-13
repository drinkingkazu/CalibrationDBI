#ifndef IOVDATA_QUALITY_CXX
#define IOVDATA_QUALITY_CXX

#include "IOVDB/IOVDBError.h"
#include "IOVDB/UtilFunc.h"
#include "Quality.h"
namespace lariov {

  Quality::Quality()
  { _quality = true; }

  void Quality::Interpret(const std::vector<std::string>& field_value_v)
  {
    if(field_value_v.size() != 1)
      throw IOVDBError("Provided string array has an incorrect length!");
    
    _quality = FromString<bool>(field_value_v[0]);
  }

  const lariov::TableDef Quality::TableDef() const
  { 
    lariov::TableDef res;
    res.Append( ColumnDef("quality",kBOOL) );
    return res;
  }

  const std::vector<std::string> Quality::ColumnValues() const
  {
    return std::vector<std::string>(1,ToString(_quality));
  }

  void Quality::Set(bool quality)
  { quality = quality; }
  
}
#endif
