#pragma once

#include <memory>
#include <string>
#include "memoryDataSet.h"
#include "pugixml.hpp"

namespace OSM {

class XmlParser {

public:
    explicit XmlParser(std::shared_ptr<MemoryDataSet> _dataSet);
    XmlParser& parse(const std::string& _xmlString);

private:
    void readOsm(const pugi::xml_node& _rootOsmNode);
    void readBounds(const pugi::xml_node& _osmElement);
    void readNote(const pugi::xml_node& _osmElement);
    void readMeta(const pugi::xml_node& _osmElement);
    void readNode(const pugi::xml_node& _osmElement);
    void readWay(const pugi::xml_node& _osmElement);
    void readRelation(const pugi::xml_node& _osmElement);
    void readTag(const pugi::xml_node& _xmlElement, std::shared_ptr<Element> _element);
    void readNd(const pugi::xml_node& _xmlElement, std::shared_ptr<Way> _way);
    void readMember(const pugi::xml_node& _xmlElement, std::shared_ptr<Relation> _relation);

    std::shared_ptr<MemoryDataSet> m_dataSet;
    pugi::xml_document m_doc;
};

}
