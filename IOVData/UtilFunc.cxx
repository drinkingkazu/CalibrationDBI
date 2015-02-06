#ifndef IOVDATA_UTILFUNC_CXX
#define IOVDATA_UTILFUNC_CXX

#include "UtilFunc.h"
namespace lariov {

  template<>
  std::string ConvertString( const std::string& value)
  { return value; }

  template<>
  double ConvertString( const std::string& value )
  { return std::stod(value); }

  template<>
  float ConvertString( const std::string& value )
  { return std::stof(value); }

  template<>
  unsigned int ConvertString( const std::string& value)
  { return std::stoul(value); }

  /*
  template<>
  int ConvertString( const std::string& value )
  { return std::stoi(value); }

  template<>
  long ConvertString( const std::string& value )
  { return std::stol(value); }

  template<>
  long long ConvertString( const std::string& value )
  { return std::stoll(value); }

  template<>
  unsigned short ConvertString( const std::string& value)
  { return std::stoul(value); }

  template<>
  unsigned long ConvertString( const std::string& value)
  { return std::stoul(value); }

  template<>
  unsigned long long ConvertString( const std::string& value)
  { return std::stoull(value); }
  */
}
#endif
