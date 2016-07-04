#include "xmlParser.h"
#include "platform.h"

using namespace rapidxml;

namespace OSM {

XmlParser::XmlParser(std::shared_ptr<DataSet> _dataSet) :
m_dataSet(_dataSet) {

}

XmlParser& XmlParser::parse(char* _xmlString) {
    try {
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
        LOGN("Element Name: %s", osmElement->name());
        osmElement = osmElement->next_sibling();
    }
}

}
