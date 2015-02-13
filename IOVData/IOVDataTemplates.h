
#ifndef IOVDATA_TEMPLATES_H
#define IOVDATA_TEMPLATES_H

#include "IOVDB/Snapshot.h"
#include "IOVDB/SnapshotCollection.h"

#include "ChDataToy.h"
template class lariov::Snapshot<lariov::ChDataToy>;
template class lariov::SnapshotCollection<lariov::ChDataToy>;

#include "Quality.h"
template class lariov::Snapshot<lariov::Quality>;
template class lariov::SnapshotCollection<lariov::Quality>;

#include "Pedestal.h"
template class lariov::Snapshot<lariov::Pedestal>;
template class lariov::SnapshotCollection<lariov::Pedestal>;

#endif
