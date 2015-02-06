#ifndef IOVDATA_UTILFUNC_H
#define IOVDATA_UTILFUNC_H

#include <string>

namespace lariov{

  template <class T>
  T ConvertString( const std::string& value );

  template<> float  ConvertString<float>(const std::string& value );
  template<> double ConvertString<double>(const std::string& value);
  template<> std::string ConvertString<std::string>(const std::string& value );

  template<> unsigned int ConvertString<unsigned int>(const std::string& value);
  /*
  template int    ConvertString<int>;
  template long   ConvertString<long>;
  */
}

#endif
