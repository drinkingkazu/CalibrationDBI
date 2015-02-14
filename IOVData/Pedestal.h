/**
 * \file Pedestal.h
 *
 * \ingroup IOVData
 * 
 * \brief Class def header for a class Pedestal
 *
 * @author kterao
 */

/** \addtogroup IOVData

    @{*/
#ifndef IOVDATA_PEDESTAL_H
#define IOVDATA_PEDESTAL_H

#include "IOVDB/ChDataBase.h"

namespace lariov{
  /**
     \class Pedestal
  */
  class Pedestal : public lariov::ChDataBase {
    
  public:
    
    /// Default constructor
    Pedestal();
    
    /// Default destructor
    ~Pedestal(){}

    void Interpret(const std::vector<std::string>& field_value_v);

    const lariov::TableDef TableDef() const;

    const std::vector<std::string> ColumnValues() const;

    void Set(float mean, float rms);

  private:

    float _mean;
    float _rms;

  };
}

#endif
/** @} */ // end of doxygen group 

