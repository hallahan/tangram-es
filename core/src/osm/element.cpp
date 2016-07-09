#include "element.h"

namespace OSM {

Element::Element(const long _id, const std::string& _versionStr, 
                     const std::string& _timestampStr, const std::string& _changesetStr, 
                     const std::string& _uidStr, const std::string& _userStr, 
                     const std::string& _actionStr, const std::string& _visibleStr) :
m_id(_id),
m_timestamp(_timestampStr),
m_user(_userStr) {

    try {
        m_version = std::stol(_versionStr);
    } catch (...) {
        m_version = 0;
    }
    
    try {
        m_changeset = std::stol(_changesetStr);
    } catch (...) {
        m_changeset = 0;
    }
    
    try {
        m_uid = std::stol(_uidStr);
    } catch (...) {
        m_uid = 0;
    }
    
    if (_actionStr == "modify") {
        m_modified = true;
    }

    if (_visibleStr == "false") {
        m_visible = false;
    } else {
        m_visible = true;
    }
}

void Element::addParsedTag(const std::string k, const std::string v) {

}

void Element::addNodeRef(long id) {

}

}
