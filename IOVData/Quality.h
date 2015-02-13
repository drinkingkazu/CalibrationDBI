/**
 * \file Quality.h
 *
 * \ingroup IOVData
 * 
 * \brief Class def header for a class Quality
 *
 * @author kterao
 */

/** \addtogroup IOVData

    @{*/
#ifndef IOVDATA_QUALITY_H
#define IOVDATA_QUALITY_H

#include "IOVDB/ChDataBase.h"

namespace lariov{
  /**
     \class Quality
  */
  class Quality : public lariov::ChDataBase {
    
  public:
    
    /// Default constructor
    Quality();
    
    /// Default destructor
    ~Quality(){}

    virtual void Interpret(const std::vector<std::string>& field_value_v);

    virtual const lariov::TableDef TableDef() const;

    virtual const std::vector<std::string> ColumnValues() const;

    void Set(bool quality);

  private:

    bool _quality;

  };
}

#endif
/** @} */ // end of doxygen group 

