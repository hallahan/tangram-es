#include "xmlParser.h"
#include "platform.h"

namespace OSM {

XmlParser::XmlParser(std::shared_ptr<MemoryDataSet> _dataSet) :
m_dataSet(_dataSet) {

}

XmlParser& XmlParser::parse(const char* _xmlString, size_t size) {
    pugi::xml_parse_result result = m_doc.load_buffer(_xmlString, size);
    if (result) {
        // LOGN("pugixml parse success: %s", _xmlString);
        readOsm(m_doc.child("osm"));
        m_dataSet->postProcess();
    } else {
        LOGE("OSM XML parse error description: %s", result.description());
        LOGE("OSM XML parse error offset: %td", result.offset);
        LOGE("OSM XML parse error XML: %s", _xmlString);
    }

    return *this;
}

void XmlParser::readOsm(const pugi::xml_node& _rootOsmNode) {
    // Iterate through all of the OSM Elements.
    for (auto osmElement : _rootOsmNode.children()) {
        std::string name = osmElement.name();
        if (name == "node") {
            readNode(osmElement);
        } else if (name == "way") {
            readWay(osmElement);
        } else if (name == "relation") {
            readRelation(osmElement);
        } else if (name == "bounds") {
            readBounds(osmElement);
        } else if (name == "note") {
            readNote(osmElement);
        } else if (name == "meta") {
            readMeta(osmElement);
        }
    }
}

void XmlParser::readBounds(const pugi::xml_node& _osmElement) {

}

void XmlParser::readNote(const pugi::xml_node& _osmElement) {

}

void XmlParser::readMeta(const pugi::xml_node& _osmElement) {

}

void XmlParser::readNode(const pugi::xml_node& _osmElement) {

    // Read Attributes
    long id = _osmElement.attribute("id").as_llong();
    double lat = _osmElement.attribute("lat").as_double();
    double lon = _osmElement.attribute("lon").as_double();
    long version = _osmElement.attribute("version").as_llong();
    std::string timestamp = _osmElement.attribute("version").as_string();
    long changeset = _osmElement.attribute("changeset").as_llong();
    long uid = _osmElement.attribute("uid").as_llong();
    std::string user = _osmElement.attribute("user").as_string();
    std::string action = _osmElement.attribute("action").as_string();
    std::string visible = _osmElement.attribute("action").as_string();

    // Create OSM Element
    std::shared_ptr<Node> n = m_dataSet->createNode(id, lat, lon, version, timestamp,
                                                    changeset, uid, user, action, visible);
    
    // get tags
    for (auto tag : _osmElement.children("tag")) {
        readTag(tag, n);
    }
}

void XmlParser::readWay(const pugi::xml_node& _osmElement) {

    // Read Attributes
    long id = _osmElement.attribute("id").as_llong();
    long version = _osmElement.attribute("version").as_llong();
    std::string timestamp = _osmElement.attribute("version").as_string();
    long changeset = _osmElement.attribute("changeset").as_llong();
    long uid = _osmElement.attribute("uid").as_llong();
    std::string user = _osmElement.attribute("user").as_string();
    std::string action = _osmElement.attribute("action").as_string();
    std::string visible = _osmElement.attribute("action").as_string();

    std::shared_ptr<Way> w = m_dataSet->createWay(id, version, timestamp, changeset,
                                                  uid, user, action, visible);

    // get tags
    for (auto tag : _osmElement.children("tag")) {
        readTag(tag, w);
    }

    // get nds
    for (auto nd : _osmElement.children("nd")) {
        readNd(nd, w);
    }
}

void XmlParser::readRelation(const pugi::xml_node& _osmElement) {

}

void XmlParser::readTag(const pugi::xml_node& _xmlElement, std::shared_ptr<Element> _element) {
    _element->addParsedTag(_xmlElement.attribute("k").value(),
                           _xmlElement.attribute("v").value());
}

void XmlParser::readNd(const pugi::xml_node& _xmlElement, std::shared_ptr<Way> _way) {
    _way->addNodeRef(_xmlElement.attribute("ref").as_llong());
}

void XmlParser::readMember(const pugi::xml_node& _xmlElement, std::shared_ptr<Relation> _relation) {

}


}
