#ifndef IOVDATA_CHDATATOY_CXX
#define IOVDATA_CHDATATOY_CXX

#include "IOVDB/IOVDBError.h"
#include "IOVDB/UtilFunc.h"
#include "ChDataToy.h"
namespace lariov {

  ChDataToy::ChDataToy()
  { _x = _y = _z = 0.; }

  void ChDataToy::Interpret(const std::vector<std::string>& field_value_v)
  {
    if(field_value_v.size() != 3)
      throw IOVDBError("Provided string array has an incorrect length!");
    
    _x = FromString<float>(field_value_v[0]);
    _y = FromString<float>(field_value_v[1]);
    _z = FromString<float>(field_value_v[2]);
  }

  const lariov::TableDef ChDataToy::TableDef() const
  { 
    lariov::TableDef res;
    res.Append( ColumnDef("x",kFLOAT) );
    res.Append( ColumnDef("y",kFLOAT) );
    res.Append( ColumnDef("z",kFLOAT) );
    return res;
  }

  const std::vector<std::string> ChDataToy::ColumnValues() const
  {
    std::vector<std::string> res(3,"");

    res[0] = ToString(_x);
    res[1] = ToString(_y);
    res[2] = ToString(_z);

    return res;
  }

  void ChDataToy::Set(double x, double y, double z)
  { _x = x; _y = y; _z = z; }

}
#endif
