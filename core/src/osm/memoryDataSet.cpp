#include "memoryDataSet.h"

namespace OSM {

MemoryDataSet::MemoryDataSet() {
    
}

void MemoryDataSet::addOSM(const std::string& version, const std::string& generator) {
    
}
    
Node MemoryDataSet::addNode(const std::string& idStr, const std::string& latStr, const std::string& lonStr, const std::string& versionStr,
             const std::string& timestampStr, const std::string& changesetStr, const std::string& uidStr,
             const std::string& userStr, const std::string& actionStr, const std::string& visibleStr) {
    
}

Way MemoryDataSet::addWay(const std::string& idStr, const std::string& versionStr,
             const std::string& timestampStr, const std::string& changesetStr, const std::string& uidStr,
             const std::string& userStr, const std::string& actionStr, const std::string& visibleStr) {
    
}

Relation MemoryDataSet::addRelation(const std::string& idStr, const std::string& versionStr,
            const std::string& timestampStr, const std::string& changesetStr, const std::string& uidStr,
            const std::string& userStr, const std::string& actionStr, const std::string& visibleStr) {
    
}

void MemoryDataSet::postProcess() {
    
}

}
