/**
 * \file TableDef.h
 *
 * \ingroup IOVDB
 * 
 * \brief Class def header for a class TableDef
 *
 * @author kterao
 */

/** \addtogroup IOVDB

    @{*/
#ifndef IOVDB_TABLEDEF_H
#define IOVDB_TABLEDEF_H

#include <vector>
#include "ColumnDef.h"

namespace lariov {
  /**
     \class TableDef
  */
  class TableDef {
  
  public:
    
    /// Default constructor
    TableDef(){}
    
    /// Default destructor
    ~TableDef(){}

    const std::vector<lariov::ColumnDef>& ColumnDefs() const;

    void Append(const lariov::ColumnDef& cl);

    int Index(const lariov::ColumnDef& cl) const;

  private:

    std::vector<lariov::ColumnDef> _columns;
    
  };
}

#endif
/** @} */ // end of doxygen group 

