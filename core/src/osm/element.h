#pragma once

#include <string>
#include <map>

namespace OSM {

// TODO - Consider using Value or PropertyItem
using Tags = std::map<std::string, std::string>;

class Element {

public:

    explicit Element(const long _id, const std::string& _versionStr, 
                     const std::string& _timestampStr, const std::string& _changesetStr, 
                     const std::string& _uidStr, const std::string& _userStr, 
                     const std::string& _actionStr, const std::string& _visibleStr);

    void addParsedTag(const std::string k, const std::string v);
    
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
