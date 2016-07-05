#include "xmlParser.h"
#include "platform.h"

using namespace rapidxml;

namespace OSM {

XmlParser::XmlParser(std::shared_ptr<MemoryDataSet> _dataSet) :
m_dataSet(_dataSet) {

}

XmlParser& XmlParser::parse(char* _xmlString) {
    try {
        //LOGN("xmlString: %s", _xmlString);
        m_doc.parse<0>(_xmlString);
        readOsm(m_doc.first_node());
    } catch (...) {
        
    }
    return *this;
}

void XmlParser::readOsm(xml_node<>* _rootOsmNode) {
    // Iterate through all of the OSM Elements.
    xml_node<>* osmElement = _rootOsmNode->first_node();
    while (osmElement) {
        std::string name = osmElement->name();
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
        osmElement = osmElement->next_sibling();
    }
}

void XmlParser::readBounds(rapidxml::xml_node<>* _osmElement) {

}

void XmlParser::readNote(rapidxml::xml_node<>* _osmElement) {

}

void XmlParser::readMeta(rapidxml::xml_node<>* _osmElement) {

}

void XmlParser::readNode(rapidxml::xml_node<>* _osmElement) {
    std::string idStr;
    std::string latStr;
    std::string lonStr;
    std::string versionStr;
    std::string timestampStr;
    std::string changesetStr;
    std::string uidStr;
    std::string userStr;
    std::string actionStr;
    std::string visibleStr;
    
    // read attributes
    xml_attribute<>* attr = _osmElement->first_attribute("id");
    if (attr) {
        idStr = attr->value();
    }
    attr = _osmElement->first_attribute("lat");
    if (attr) {
        latStr = attr->value();
    }
    attr = _osmElement->first_attribute("lon");
    if (attr) {
        lonStr = attr->value();
    }
    attr = _osmElement->first_attribute("version");
    if (attr) {
        versionStr = attr->value();
    }
    attr = _osmElement->first_attribute("timestamp");
    if (attr) {
        timestampStr = attr->value();
    }
    attr = _osmElement->first_attribute("changeset");
    if (attr) {
        changesetStr = attr->value();
    }
    attr = _osmElement->first_attribute("uid");
    if (attr) {
        uidStr = attr->value();
    }
    attr = _osmElement->first_attribute("user");
    if (attr) {
        userStr = attr->value();
    }
    attr = _osmElement->first_attribute("action");
    if (attr) {
        actionStr = attr->value();
    }
    attr = _osmElement->first_attribute("visible");
    if (attr) {
        visibleStr = attr->value();
    }

    Node n = m_dataSet->addNode(idStr, latStr, lonStr, versionStr, timestampStr,
                                changesetStr, uidStr, userStr, actionStr, visibleStr);
    
    // get tags
    rapidxml::xml_node<>* elChild = _osmElement->first_node();
    if (elChild) {
        std::string name = elChild->name();
        if (name == "tag") {
            readTag(elChild, n);
        } 
        elChild = elChild->next_sibling();
    }
}

void XmlParser::readWay(rapidxml::xml_node<>* _osmElement) {
    std::string idStr;
    std::string versionStr;
    std::string timestampStr;
    std::string changesetStr;
    std::string uidStr;
    std::string userStr;
    std::string actionStr;
    std::string visibleStr;

    xml_attribute<>* attr = _osmElement->first_attribute("id");
    if (attr) {
        idStr = attr->value();
    }
    attr = _osmElement->first_attribute("version");
    if (attr) {
        versionStr = attr->value();
    }
    attr = _osmElement->first_attribute("timestamp");
    if (attr) {
        timestampStr = attr->value();
    }
    attr = _osmElement->first_attribute("changeset");
    if (attr) {
        changesetStr = attr->value();
    }
    attr = _osmElement->first_attribute("uid");
    if (attr) {
        uidStr = attr->value();
    }
    attr = _osmElement->first_attribute("user");
    if (attr) {
        userStr = attr->value();
    }
    attr = _osmElement->first_attribute("action");
    if (attr) {
        uidStr = attr->value();
    }
    attr = _osmElement->first_attribute("visible");
    if (attr) {
        userStr = attr->value();
    }

    Way w = m_dataSet->addWay(idStr, versionStr, timestampStr, changesetStr,
                              uidStr, userStr, actionStr, visibleStr);

    // get nds, tags
    rapidxml::xml_node<>* elChild = _osmElement->first_node();
    while (elChild) {
        std::string name = elChild->name();
        if (name == "tag") {
            readTag(elChild, w);
        } else if (name == "nd") {
            readNd(elChild, w);
        }
        elChild = elChild->next_sibling();
    }

}

void XmlParser::readRelation(rapidxml::xml_node<>* _osmElement) {

}

void XmlParser::readTag(rapidxml::xml_node<>* _osmElement, const Element& _element) {
    xml_attribute<>* kAttr = _osmElement->first_attribute("k");
    xml_attribute<>* vAttr = _osmElement->first_attribute("v");
    if (kAttr && vAttr) {
        
    }
}

void XmlParser::readNd(rapidxml::xml_node<>* _osmElement, const Element& _element) {

}

void XmlParser::readMember(rapidxml::xml_node<>* _osmElement, const Element& _element) {

}


}
