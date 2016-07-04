#pragma once

#include "dataSet.h"

namespace OSM {

class MemoryDataSet : public DataSet {

public:
    explicit MemoryDataSet();

private:
    int i;
};

}
