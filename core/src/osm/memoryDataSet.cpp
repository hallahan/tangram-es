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
    m_wayNodeIds.insert(id);
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
    // TODO
    return nullptr;
}

void MemoryDataSet::postProcess() {
    // iterate through ways
    for (auto const& wPair : m_ways) {
        std::shared_ptr<Way> w = wPair.second;
        w->linkNodes(m_nodes, m_wayNodeIds);
        
        /**
         * If a way has the same starting node as ending node,
         * it is a closed way.
         */
        if (w->isClosed()) {
            m_closedWays.push_back(w);
        } else {
            m_openWays.push_back(w);
        }
    }
    
}

Tangram::Layer MemoryDataSet::getLayer(const Tangram::GeoJson::Transform& _proj, int32_t _sourceId) {
    Tangram::Layer layer("osmXml");

    // polygons

    // lines

    // points


    return layer;
}

}
