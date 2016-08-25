#include "memoryDataSet.h"

#include "data/propertyItem.h"

namespace OSM {

MemoryDataSet::MemoryDataSet() {
    
}

void MemoryDataSet::addOSM(const std::string& version, const std::string& generator) {
    
}
    
std::shared_ptr<Node> MemoryDataSet::createNode(const long _id, const double _lat, const double _lon, const long _version,
                                                const std::string& _timestamp, const long _changeset, const long _uid,
                                                const std::string& _user, const std::string& _action, const std::string& _visible) {

    std::shared_ptr<Node> n = std::make_shared<Node>(   _id, _lat, _lon, _version,
                                                        _timestamp, _changeset, _uid,
                                                        _user, _action, _visible );
    m_nodes[_id] = n;
    m_wayNodeIds.insert(_id);
    return n;
}

std::shared_ptr<Way> MemoryDataSet::createWay(const long _id, const long _version,
                                              const std::string& _timestamp, const long _changeset, const long _uid,
                                              const std::string& _user, const std::string& _action, const std::string& _visible) {
    
    std::shared_ptr<Way> w = std::make_shared<Way>(  _id, _version, _timestamp, _changeset,
                                                    _uid, _user, _action, _visible );
    m_ways[_id] = w;
    return w;
}

std::shared_ptr<Relation> MemoryDataSet::createRelation(const long _id, const long _version,
                                                        const std::string& _timestamp, const long _changeset, const long _uid,
                                                        const std::string& _user, const std::string& _action, const std::string& _visible) {
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

size_t MemoryDataSet::size() {
    return m_nodes.size() + m_ways.size() + m_relations.size();
}

Tangram::Layer MemoryDataSet::getLayer(const Transform& _proj, int32_t _sourceId) {
    Tangram::Layer layer("osmXml");

    // polygons
    for (const auto& closedWay : m_closedWays) {
       layer.features.push_back(getPolygonFeature(*closedWay, _proj, _sourceId));    
    }

    // lines
    for (auto const& openWay : m_openWays) {
        layer.features.push_back(getLineFeature(*openWay, _proj, _sourceId));    
    }

    // points
    for (auto const& standaloneNode : m_standaloneNodes) {
        layer.features.push_back(getPointFeature(*standaloneNode, _proj, _sourceId));    
    }

    return layer;
}

Tangram::Feature MemoryDataSet::getPolygonFeature(const Way& _closedWay, const Transform& _proj, int32_t _sourceId) {
    Tangram::Feature feature;

    // Copy properties into tile data
    feature.props = getProperties(_closedWay.tags(), _sourceId);
    
    // Copy geometry into tile data
    feature.polygons.push_back(getPolygon(_closedWay.nodes(), _proj));
    
    return feature;
}

Tangram::Feature MemoryDataSet::getLineFeature(const Way& _openWay, const Transform& _proj, int32_t _sourceId) {
    Tangram::Feature feature;

    // Copy properties into tile data
    feature.props = getProperties(_openWay.tags(), _sourceId);
    
    // Copy geometry into tile data
    feature.lines.push_back(getLine(_openWay.nodes(), _proj));
    
    return feature;
}

Tangram::Feature MemoryDataSet::getPointFeature(const Node& _standaloneNode, const Transform& _proj, int32_t _sourceId) {
    Tangram::Feature feature;
    
    // Copy properties into tile data
    feature.props = getProperties(_standaloneNode.tags(), _sourceId);
    
    // Copy geometry into tile data
    feature.points.push_back(getPoint(_standaloneNode, _proj));

    return feature;
}

Tangram::Polygon MemoryDataSet::getPolygon(const std::vector<std::shared_ptr<Node>>& _nodes , const Transform& _proj) {
    Tangram::Polygon polygon;

    polygon.push_back(getLine(_nodes, _proj));
    
    return polygon;
}

Tangram::Line MemoryDataSet::getLine(const std::vector<std::shared_ptr<Node>>& _nodes , const Transform& _proj) {
    Tangram::Line line;

    for (const auto& n : _nodes) {
        line.push_back(getPoint(*n, _proj));
    }

    return line;
}

Tangram::Point MemoryDataSet::getPoint(const Node& _node, const Transform& _proj) {
    return _proj(_node.lonLat());
}

Tangram::Properties MemoryDataSet::getProperties(const Tags& _tags, int32_t _sourceId) {
   std::vector<Tangram::PropertyItem> items;
   items.reserve(_tags.size());

    for (const auto& tag : _tags) {
        // A number value should be a double
        try {
            double val = std::stod(tag.second);
            items.emplace_back(tag.first, val);
        } 
        // Not a number, so keep as string.
        catch (...) {
            items.emplace_back(tag.first, tag.second);
        }
    }

    Tangram::Properties properties;
    properties.sourceId = _sourceId;
    properties.setSorted(std::move(items));
    properties.sort();
    
    return properties;
}


}
