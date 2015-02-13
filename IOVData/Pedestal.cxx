#ifndef IOVDATA_PEDESTAL_CXX
#define IOVDATA_PEDESTAL_CXX

#include "IOVDB/IOVDBError.h"
#include "IOVDB/UtilFunc.h"
#include "Pedestal.h"
namespace lariov {

  Pedestal::Pedestal()
  { _mean = _rms = -1.; }

  void Pedestal::Interpret(const std::vector<std::string>& field_value_v)
  {
    if(field_value_v.size() != 2)
      throw IOVDBError("Provided string array has an incorrect length!");
    
    _mean = FromString<float>(field_value_v[0]);
    _rms  = FromString<float>(field_value_v[1]);
  }

  const lariov::TableDef Pedestal::TableDef() const
  { 
    lariov::TableDef res;
    res.Append( ColumnDef("mean",kFLOAT) );
    res.Append( ColumnDef("rms", kFLOAT) );
    return res;
  }

  const std::vector<std::string> Pedestal::ColumnValues() const
  {
    std::vector<std::string> res(2,"");
    res[0] = ToString(_mean);
    res[1] = ToString(_rms );
    return res;
  }

  void Pedestal::Set(float mean, float rms)
  { _mean = mean; _rms = rms; }
  
}
#endif
