/**
 * \file ChDataBase.h
 *
 * \ingroup IOVDB
 * 
 * \brief Class def header for a class ChDataBase
 *
 * @author kterao
 */

/** \addtogroup IOVDB

    @{*/
#ifndef IOVDB_CHDATABASE_H
#define IOVDB_CHDATABASE_H

#include <vector>
#include <string>
#include "TableDef.h"
namespace lariov {

  /**
     \class ChDataBase
  */
  class ChDataBase {
    
  public:
    
    /// Default constructor
    ChDataBase() {}
    
    /// Default destructor
    virtual ~ChDataBase(){}

    void Channel(unsigned int ch) { _ch = ch;   }

    unsigned int Channel() const  { return _ch; }

    inline bool operator<(const ChDataBase& ch) const
    { return _ch < ch.Channel(); }

    inline bool operator<(const unsigned int& ch) const
    { return _ch < ch; }

    virtual void Interpret(const std::vector<std::string>& field_value_v) = 0;

    virtual const lariov::TableDef TableDef() const = 0;

    virtual const std::vector<std::string> ColumnValues() const = 0;

  protected:

    unsigned int _ch;
    
  };
}

namespace std {
  template<>
  class less<lariov::ChDataBase>
  {
  public:
    bool operator()( const lariov::ChDataBase* lhs, const lariov::ChDataBase* rhs )
    { return (*lhs) < (*rhs); }
  };
}

#endif
/** @} */ // end of doxygen group 

