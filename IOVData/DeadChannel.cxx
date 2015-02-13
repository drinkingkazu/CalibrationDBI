#ifndef IOVDATA_DEADCHANNEL_CXX
#define IOVDATA_DEADCHANNEL_CXX

#include "IOVDB/IOVDBError.h"
#include "IOVDB/UtilFunc.h"
#include "DeadChannel.h"
namespace lariov {

  DeadChannel::DeadChannel()
  { _dead = false; }

  void DeadChannel::Interpret(const std::vector<std::string>& field_value_v)
  {
    if(field_value_v.size() != 1)
      throw IOVDBError("Provided string array has an incorrect length!");
    
    _dead = FromString<bool>(field_value_v[0]);
  }

  const lariov::TableDef DeadChannel::TableDef() const
  { 
    lariov::TableDef res;
    res.Append( ColumnDef("dead",kBOOL) );
    return res;
  }

  const std::vector<std::string> DeadChannel::ColumnValues() const
  {
    return std::vector<std::string>(1,(_dead ? "true" : "false"));
  }

  void DeadChannel::Set(bool dead)
  { _dead = dead; }

}
#endif
