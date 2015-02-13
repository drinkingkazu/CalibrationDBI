#ifndef WEBDBI_TEMPLATES_H
#define WEBDBI_TEMPLATES_H

#include "WebReader.h"

#include "IOVData/ChDataToy.h"
template class lariov::WebReader<lariov::ChDataToy>;

#include "IOVData/Quality.h"
template class lariov::WebReader<lariov::Quality>;

#include "IOVData/Pedestal.h"
template class lariov::WebReader<lariov::Pedestal>;

#endif
