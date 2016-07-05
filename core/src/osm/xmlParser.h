#pragma once

#include <memory>
#include <string>
#include "memoryDataSet.h"
#include "rapidxml/rapidxml.hpp"

namespace OSM {

class XmlParser {

public:
    explicit XmlParser(std::shared_ptr<MemoryDataSet> _dataSet);
    XmlParser& parse(char* _xmlString);

private:
    void readOsm(rapidxml::xml_node<>* _rootOsmNode);
    void readBounds(rapidxml::xml_node<>* _osmElement);
    void readNote(rapidxml::xml_node<>* _osmElement);
    void readMeta(rapidxml::xml_node<>* _osmElement);
    void readNode(rapidxml::xml_node<>* _osmElement);
    void readWay(rapidxml::xml_node<>* _osmElement);
    void readRelation(rapidxml::xml_node<>* _osmElement);
    void readTag(rapidxml::xml_node<>* _osmElement, const Element& _element);
    void readNd(rapidxml::xml_node<>* _osmElement, const Element& _element);
    void readMember(rapidxml::xml_node<>* _osmElement, const Element& _element);

    std::shared_ptr<MemoryDataSet> m_dataSet;
    rapidxml::xml_document<> m_doc;
};

}
