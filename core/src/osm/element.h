#pragma once

#include <string>
#include <map>

namespace OSM {

// TODO - Consider using Value or PropertyItem
using Tags = std::map<std::string, std::string>;

class Element {

public:

    explicit Element(const long _id, const long _version,
                     const std::string& _timestamp, const long _changeset,
                     const long _uid, const std::string& _user,
                     const std::string& _action, const std::string& _visible);

    void addParsedTag(const std::string& k, const std::string& v);
    
    // Read only tag accessor
    const Tags& tags() const { return m_tags; };
    
protected:
    long m_id;
    long m_version;
    std::string m_timestamp;
    long m_changeset;
    long m_uid;
    std::string m_user;
    bool m_modified;
    bool m_visible;
    
    Tags m_tags;
};

}
