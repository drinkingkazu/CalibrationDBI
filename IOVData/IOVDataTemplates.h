
#ifndef IOVDATA_TEMPLATES_H
#define IOVDATA_TEMPLATES_H

#include "IOVDB/Snapshot.h"
#include "IOVDB/SnapshotCollection.h"

#include "ChDataToy.h"

template class lariov::Snapshot<lariov::ChDataToy>;
template class lariov::SnapshotCollection<lariov::ChDataToy>;

#endif
