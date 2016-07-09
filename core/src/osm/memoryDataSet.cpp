#include "memoryDataSet.h"

namespace OSM {

MemoryDataSet::MemoryDataSet() {
    
}

void MemoryDataSet::addOSM(const std::string& version, const std::string& generator) {
    
}
    
std::shared_ptr<Node> MemoryDataSet::createNode(const std::string& _idStr, const std::string& _latStr, const std::string& _lonStr, const std::string& _versionStr,
             const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
             const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr) {

    long id = std::stol(_idStr);
    std::shared_ptr<Node> n = std::make_shared<Node>(   id, _latStr, _lonStr, _versionStr, 
                                                        _timestampStr, _changesetStr, _uidStr, 
                                                        _userStr, _actionStr, _visibleStr );
    m_nodes[id] = n;
    return n;
}

std::shared_ptr<Way> MemoryDataSet::createWay(const std::string& _idStr, const std::string& _versionStr,
             const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
             const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr) {
    
    long id = std::stol(_idStr);
    std::shared_ptr<Way> w = std::make_shared<Way>(  id, _versionStr, _timestampStr, _changesetStr, 
                                                    _uidStr, _userStr, _actionStr, _visibleStr );
    m_ways[id] = w;
    return w;
}

std::shared_ptr<Relation> MemoryDataSet::createRelation(const std::string& _idStr, const std::string& _versionStr,
            const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
            const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr) {
    
}

void MemoryDataSet::postProcess() {
    
}

}
