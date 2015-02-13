/**
 * \file DeadChannel.h
 *
 * \ingroup IOVData
 * 
 * \brief Class def header for a class DeadChannel
 *
 * @author kterao
 */

/** \addtogroup IOVData

    @{*/
#ifndef IOVDATA_DEADCHANNEL_H
#define IOVDATA_DEADCHANNEL_H

#include "IOVDB/ChDataBase.h"

namespace lariov{
  /**
     \class DeadChannel
  */
  class DeadChannel : public lariov::ChDataBase {
    
  public:
    
    /// Default constructor
    DeadChannel();
    
    /// Default destructor
    ~DeadChannel(){}

    virtual void Interpret(const std::vector<std::string>& field_value_v);

    virtual const lariov::TableDef TableDef() const;

    virtual const std::vector<std::string> ColumnValues() const;

    void Set(bool dead);

  private:

    bool _dead;

  };
}

#endif
/** @} */ // end of doxygen group 

