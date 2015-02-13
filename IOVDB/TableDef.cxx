#ifndef IOVDB_TABLEDEF_CXX
#define IOVDB_TABLEDEF_CXX

#include "TableDef.h"
#include "IOVDBError.h"
namespace lariov {

  const std::vector<lariov::ColumnDef>& TableDef::ColumnDefs() const
  { return _columns; }
 
  void TableDef::Append(const lariov::ColumnDef& cl)
  {
    for(auto const& my_cl : _columns) 
      if( Index(cl)>=0 )
	throw IOVDBError("Columns cannot have the same name!");
    _columns.push_back(cl);
  }
  
  int TableDef::Index(const lariov::ColumnDef& cl) const
  {
    int res=-1;
    for(size_t i=0; i<_columns.size(); ++i) {
      if(_columns[i].Name() == cl.Name()) {
	res=i;
	break;
      }
    }
    return res;
  }
}

#endif
