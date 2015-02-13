/**
 * \file ChDataToy.h
 *
 * \ingroup IOVData
 * 
 * \brief Class def header for a class ChDataToy
 *
 * @author kterao
 */

/** \addtogroup IOVData

    @{*/
#ifndef IOVDATA_CHDATATOY_H
#define IOVDATA_CHDATATOY_H

#include "IOVDB/ChDataBase.h"

namespace lariov{
  /**
     \class ChDataToy
  */
  class ChDataToy : public lariov::ChDataBase {
    
  public:
    
    /// Default constructor
    ChDataToy();
    
    /// Default destructor
    ~ChDataToy(){}

    virtual void Interpret(const std::vector<std::string>& field_value_v);

    virtual const lariov::TableDef TableDef() const;

    virtual const std::vector<std::string> ColumnValues() const;

    void Set(double x, double y, double z);

  private:

    double _x, _y, _z;

  };
}

#endif
/** @} */ // end of doxygen group 

