#ifndef IOVDATA_TPCCALIB_CXX
#define IOVDATA_TPCCALIB_CXX

#include "IOVDB/IOVDBError.h"
#include "IOVDB/UtilFunc.h"
#include "TPCCalib.h"
namespace lariov {

  TPCCalib::TPCCalib()
  { 
    _pedestal = 0;
    _rmsnoise = 0;
    _areagain = 0;
    _ampgain  = 0;
  }

  void TPCCalib::Interpret(const std::vector<std::string>& field_value_v)
  {
    if(field_value_v.size() != 4)
      throw IOVDBError("Provided string array has an incorrect length!");
    
    _pedestal = FromString<float>(field_value_v[0]);
    _rmsnoise = FromString<float>(field_value_v[1]);
    _areagain = FromString<float>(field_value_v[2]);
    _ampgain  = FromString<float>(field_value_v[2]);
  }

  const lariov::TableDef TPCCalib::TableDef() const
  { 
    lariov::TableDef res;
    res.Append( ColumnDef("pedestal",kFLOAT) );
    res.Append( ColumnDef("RMS noise",kFLOAT) );
    res.Append( ColumnDef("Area Gain",kFLOAT) );
    res.Append( ColumnDef("Amp Gain",kFLOAT) );
    return res;
  }

  const std::vector<std::string> TPCCalib::ColumnValues() const
  {
    std::vector<std::string> res(4,"");

    res[0] = ToString(_pedestal);
    res[1] = ToString(_rmsnoise);
    res[2] = ToString(_areagain);
    res[3] = ToString(_ampgain);

    return res;
  }

  void TPCCalib::Set(float pedestal, float rmsnoise, float areagain, float ampgain)
  {
    _pedestal = pedestal;
    _rmsnoise = rmsnoise;
    _areagain = areagain;
    _ampgain  = ampgain;
  }

}
#endif
