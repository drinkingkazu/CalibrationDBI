/**
 * \file ColumnDef.h
 *
 * \ingroup IOVDB
 * 
 * \brief Class def header for a class ColumnDef
 *
 * @author kterao
 */

/** \addtogroup IOVDB

    @{*/
#ifndef IOVDB_COLUMNDEF_H
#define IOVDB_COLUMNDEF_H

#include <utility>
#include <string>
#include "IOVDBTypes.h"

namespace lariov {
  /**
     \class ColumnDef
  */
  class ColumnDef {
    
  public:
    
    /// Default constructor
    ColumnDef(const std::string name="noname",
	      const ValueType_t type=kUNKNOWN);
    
    /// Default destructor
    ~ColumnDef(){}

    const std::string& Name() const;

    const lariov::ValueType_t& Type() const;

    inline bool operator<(const ColumnDef& cl) const
    { return this->_name < cl.Name(); }
    
  private:

    std::string _name;

    lariov::ValueType_t _type;
    
  };
}

namespace std {
  template<>
  class less<lariov::ColumnDef>
  {
  public:
    bool operator()( const lariov::ColumnDef* lhs, const lariov::ColumnDef* rhs )
    { return (*lhs) < (*rhs); }
  };
}

#endif
/** @} */ // end of doxygen group 

