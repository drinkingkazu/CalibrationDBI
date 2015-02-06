/**
 * \file ChData.h
 *
 * \ingroup IOVData
 * 
 * \brief Class def header for a class ChData
 *
 * @author kterao
 */

/** \addtogroup IOVData

    @{*/
#ifndef IOVDATA_CHDATA_H
#define IOVDATA_CHDATA_H

#include <vector>
namespace lariov {
  /**
     \class ChData
  */
  template <class T>
  class ChData : public std::vector<T> {
    
  public:
    
    /// Default constructor
    ChData() : std::vector<T>() {}
    
    /// Default destructor
    ~ChData(){}

    void Channel(unsigned int ch) { _ch = ch;   }

    unsigned int Channel() const  { return _ch; }

    template <class U>
    inline bool operator<(const U& rhs) const
    { return _ch < rhs;}

    inline bool operator<(const ChData& ch) const
    { return _ch < ch.Channel(); }

  protected:

    unsigned int _ch;
    
  };
}
#endif
/** @} */ // end of doxygen group 
