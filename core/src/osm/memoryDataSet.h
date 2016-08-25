#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
#include <functional>

#include "dataSet.h"
#include "node.h"
#include "way.h"
#include "relation.h"
#include "data/tileData.h"

namespace OSM {

using Transform = std::function<Tangram::Point(glm::dvec2 _lonLat)>;

class MemoryDataSet : public DataSet {

public:
    explicit MemoryDataSet();

    // OSM Element found at beginning of XML Document
    void addOSM(const std::string& version, const std::string& generator);
    
    std::shared_ptr<Node> createNode(const long _id, const double _lat, const double _lon, const long _version,
                 const std::string& _timestamp, const long _changeset, const long _uid,
                 const std::string& _user, const std::string& _action, const std::string& _visible);
    
    std::shared_ptr<Way> createWay(const long _id, const long _version,
                 const std::string& _timestamp, const long _changeset, const long _uid,
                 const std::string& _user, const std::string& _action, const std::string& _visible);
    
    std::shared_ptr<Relation> createRelation(const long _id, const long _version,
                const std::string& _timestamp, const long _changeset, const long _uid,
                const std::string& _user, const std::string& _action, const std::string& _visible);
    
    /**
     * Done after parsing is complete, 
     * used to connect the OSM Elements together.
     */
    void postProcess();

    const std::vector<std::shared_ptr<Way>>& closedWays() const { return m_closedWays; }
    const std::vector<std::shared_ptr<Way>>& openWays() const { return m_openWays; }
    const std::vector<std::shared_ptr<Node>>& standaloneNodes() const { return m_standaloneNodes; }

    size_t size();

    Tangram::Layer getLayer(const Transform& _proj, int32_t _sourceId);

private:

    /**
     * OSM -> Tangram Layer functions
     */
    Tangram::Feature getPolygonFeature(const Way& _closedWay, const Transform& _proj, int32_t _sourceId);
    Tangram::Feature getLineFeature(const Way& _openWay, const Transform& _proj, int32_t _sourceId);
    Tangram::Feature getPointFeature(const Node& _standaloneNode, const Transform& _proj, int32_t _sourceId);
    Tangram::Polygon getPolygon(const std::vector<std::shared_ptr<Node>>& _nodes, const Transform& _proj);
    Tangram::Line getLine(const std::vector<std::shared_ptr<Node>>& _nodes, const Transform& _proj);
    Tangram::Point getPoint(const Node& _node, const Transform& _proj);
    Tangram::Properties getProperties(const Tags& _tags, int32_t _sourceId);

    /**
     * OSM Topology Containers
     */
    std::map<long, std::shared_ptr<Node>> m_nodes;
    std::map<long, std::shared_ptr<Way>> m_ways;
    std::map<long, std::shared_ptr<Relation>> m_relations;

    // Used to check for standalone nodes.
    std::set<long> m_wayNodeIds;

    /**
     * m_closedWays are Polygons
     * m_openWays are Lines
     * m_standaloneNodes are Points
     */
    std::vector<std::shared_ptr<Way>> m_closedWays;
    std::vector<std::shared_ptr<Way>> m_openWays;
    std::vector<std::shared_ptr<Node>> m_standaloneNodes;

};

}
