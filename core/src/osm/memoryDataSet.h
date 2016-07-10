#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

#include "dataSet.h"
#include "node.h"
#include "way.h"
#include "relation.h"
#include "util/GeoJson.h"

namespace OSM {

class MemoryDataSet : public DataSet {

public:
    explicit MemoryDataSet();

    // OSM Element found at beginning of XML Document
    void addOSM(const std::string& version, const std::string& generator);
    
    std::shared_ptr<Node> createNode(const std::string& _idStr, const std::string& _latStr, const std::string& _lonStr, const std::string& _versionStr,
                 const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
                 const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr);
    
    std::shared_ptr<Way> createWay(const std::string& _idStr, const std::string& _versionStr,
                 const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
                 const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr);
    
    std::shared_ptr<Relation> createRelation(const std::string& _idStr, const std::string& _versionStr,
                const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
                const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr);
    
    void postProcess();

    std::vector<std::shared_ptr<Way>> closedWays() { return m_closedWays; }
    std::vector<std::shared_ptr<Way>> openWays() { return m_openWays; }
    std::vector<std::shared_ptr<Node>> standaloneNodes() { return m_standaloneNodes; }
    
    Tangram::Layer getLayer(const Tangram::GeoJson::Transform& _proj, int32_t _sourceId);

private:
    std::map<long, std::shared_ptr<Node>> m_nodes;
    std::map<long, std::shared_ptr<Way>> m_ways;
    std::map<long, std::shared_ptr<Relation>> m_relations;

    // used to check for standalone nodes
    std::set<long> m_wayNodeIds;

    std::vector<std::shared_ptr<Way>> m_closedWays;
    std::vector<std::shared_ptr<Way>> m_openWays;
    std::vector<std::shared_ptr<Node>> m_standaloneNodes;

};

}
