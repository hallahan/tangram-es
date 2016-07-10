#include "memoryDataSet.h"

#include "data/propertyItem.h"

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
    
    
    return feature;
}

Tangram::Feature MemoryDataSet::getLineFeature(const Way& _openWay, const Transform& _proj, int32_t _sourceId) {
    Tangram::Feature feature;

    return feature;
}

Tangram::Feature MemoryDataSet::getPointFeature(const Node& _standaloneNode, const Transform& _proj, int32_t _sourceId) {
    Tangram::Feature feature;

    return feature;
}

Tangram::Polygon MemoryDataSet::getPolygon(const Way&, const Transform& _proj) {
    Tangram::Polygon polygon;

    return polygon;
}

Tangram::Line MemoryDataSet::getLine(const Way&, const Transform& _proj) {
    Tangram::Line line;

    return line;
}

Tangram::Point MemoryDataSet::getPoint(const Node&, const Transform& _proj) {
    Tangram::Point point;

    return point;
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
