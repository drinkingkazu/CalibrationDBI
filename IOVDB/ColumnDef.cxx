#ifndef IOVDB_COLUMNDEF_CXX
#define IOVDB_COLUMNDEF_CXX

#include "ColumnDef.h"
#include <algorithm>

namespace lariov {

  ColumnDef::ColumnDef(const std::string name,
		       const ValueType_t type)
    : _name (name)
    , _type (type)
  { std::transform(_name.begin(), _name.end(), _name.begin(), ::tolower); }

  const std::string& ColumnDef::Name() const
  { return _name; }

  const lariov::ValueType_t& ColumnDef::Type() const
  { return _type; }

}

#endif
