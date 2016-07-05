#pragma once

#include <string>
#include "dataSet.h"
#include "node.h"
#include "way.h"
#include "relation.h"

namespace OSM {

class MemoryDataSet : public DataSet {

public:
    explicit MemoryDataSet();

    // OSM Element found at beginning of XML Document
    void addOSM(const std::string& version, const std::string& generator);
    
    Node addNode(const std::string& idStr, const std::string& latStr, const std::string& lonStr, const std::string& versionStr,
                 const std::string& timestampStr, const std::string& changesetStr, const std::string& uidStr,
                 const std::string& userStr, const std::string& actionStr, const std::string& visibleStr);
    
    Way addWay(const std::string& idStr, const std::string& versionStr,
                 const std::string& timestampStr, const std::string& changesetStr, const std::string& uidStr,
                 const std::string& userStr, const std::string& actionStr, const std::string& visibleStr);
    
    Relation addRelation(const std::string& idStr, const std::string& versionStr,
                const std::string& timestampStr, const std::string& changesetStr, const std::string& uidStr,
                const std::string& userStr, const std::string& actionStr, const std::string& visibleStr);
    
    void postProcess();

private:
    
};

}
