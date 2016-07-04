#pragma once

#include <memory>
#include "dataSet.h"
#include "rapidxml/rapidxml.hpp"

namespace OSM {

class XmlParser {

public:
    explicit XmlParser(std::shared_ptr<DataSet> _dataSet);
    XmlParser& parse(char* _xmlString);

private:
    void readOsm(rapidxml::xml_node<>* _rootOsmNode);
    void readNote();
    void readMeta();
    void readNode();
    void readWay();
    void readRelation();
    void readTag();
    void readNd();
    void readMember();

    std::shared_ptr<DataSet> m_dataSet;
    rapidxml::xml_document<> m_doc;
};

}
