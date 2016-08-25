#include "element.h"

namespace OSM {

Element::Element(const long _id, const long _version,
                     const std::string& _timestamp, const long _changeset,
                     const long _uid, const std::string& _user,
                     const std::string& _action, const std::string& _visible) :
m_id(_id),
m_version(_version),
m_timestamp(_timestamp),
m_changeset(_changeset),
m_uid(_uid),
m_user(_user) {
    
    m_modified = _action == "modify";
    m_visible = !(_visible == "false");
}

void Element::addParsedTag(const std::string& k, const std::string& v) {
    m_tags[k] = v;
}

}
