#ifndef IOVDB_CONSTANTS_H
#define IOVDB_CONSTANTS_H

#include <TTimeStamp.h>
#include <string>
#include <climits>
#include <limits>
#include <time.h>
namespace lariov {

  const std::string kTREE_PREFIX = "iov";
  const int kMAX_INT = std::numeric_limits<int>::max();
  const TTimeStamp kMAX_TIME = TTimeStamp(kMAX_INT,kMAX_INT);
  const TTimeStamp kMIN_TIME = TTimeStamp(0,0);
}
#endif
