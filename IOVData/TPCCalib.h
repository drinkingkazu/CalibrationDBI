/**
 * \file TPCCalib.h
 *
 * \ingroup IOVData
 * 
 * \brief Class def header for a class TPCCalib
 *
 * @author kterao
 */

/** \addtogroup IOVData

    @{*/
#ifndef IOVDATA_TPCCALIB_H
#define IOVDATA_TPCCALIB_H

#include "IOVDB/ChDataBase.h"

namespace lariov{
  /**
     \class TPCCalib
  */
  class TPCCalib : public lariov::ChDataBase {
    
  public:
    
    /// Default constructor
    TPCCalib();
    
    /// Default destructor
    ~TPCCalib(){}

    void Interpret(const std::vector<std::string>& field_value_v);
    
    const lariov::TableDef TableDef() const;

    const std::vector<std::string> ColumnValues() const;

    void Set(float pedestal, float rmsnoise, float areagain, float ampgain);

  private:

    float _pedestal;
    float _rmsnoise;
    float _areagain;
    float _ampgain;

  };
}

#endif
/** @} */ // end of doxygen group 

