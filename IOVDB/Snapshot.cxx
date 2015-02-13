#ifndef IOVDB_SNAPSHOT_CXX
#define IOVDB_SNAPSHOT_CXX

#include <algorithm>
#include "Snapshot.h"
#include "UtilFunc.h"
#include "IOVDBError.h"

namespace lariov {

  template <class T>
  Snapshot<T>::Snapshot(std::string folder)
    : _folder(folder)
  {
    std::transform(_folder.begin(), _folder.end(), _folder.begin(), ::tolower);
    this->clear();
  }

  template <class T>
  void Snapshot<T>::clear()
  { 
    _data.clear();
    _iov_start = kMAX_TIME;
    _iov_end = kMAX_TIME;
  }

  template <class T>
  void Snapshot<T>::reserve(size_t n)
  { _data.reserve(n); }

  template <class T>
  const std::string& Snapshot<T>::Folder () const { return _folder;      }

  template <class T>
  const TTimeStamp&  Snapshot<T>::Start() const { return _iov_start; }

  template <class T>
  const TTimeStamp&  Snapshot<T>::End()   const { return _iov_end;   }

  template <class T>
  const std::string& Snapshot<T>::Tag() const { return _tag; }

  template <class T>
  bool  Snapshot<T>::Valid(const TTimeStamp& ts) const 
  { return (_iov_start < ts && ts < _iov_end); }

  template <class T>
  size_t Snapshot<T>::NChannels() const { return _data.size();      }

  template <class T>
  const std::vector<T>& Snapshot<T>::ChData() const { return _data; }

  template <class T>
  const TableDef Snapshot<T>::TableDef() const
  { 
    if(_data.size()) return _data[0].TableDef();
    return T().TableDef();
  }

  template <class T>
  bool Snapshot<T>::Compat(const Snapshot<T>& data) const
  {
    if(data.Folder() != _folder) return false;
    if(data.Tag() != _tag) return false;
    return true;
  }

  template <class T>
  void Snapshot<T>::Reset (const TTimeStamp iov_start)
  {
    this->clear();
    _iov_start = iov_start;
    _iov_end   = kMAX_TIME;
  }

  template <class T>
  void Snapshot<T>::Reset(const TTimeStamp& start, const TTimeStamp& end, const std::string tag)
  {
    if(start >= end)
      throw IOVDBError("Cannot set start time >= end time!");
    this->clear();
    _iov_start = start;
    _iov_end   = end;
    _tag = tag;
  }

}

#endif
