#pragma once

#include <string>
#include <map>

namespace OSM {

class Element {

public:

    explicit Element(const long _id, const std::string& _versionStr, 
                     const std::string& _timestampStr, const std::string& _changesetStr, 
                     const std::string& _uidStr, const std::string& _userStr, 
                     const std::string& _actionStr, const std::string& _visibleStr);

    void addParsedTag(const std::string k, const std::string v);
    void addNodeRef(long id);
    
protected:
    long m_id;
    long m_version;
    std::string m_timestamp;
    long m_changeset;
    long m_uid;
    std::string m_user;
    bool m_modified;
    bool m_visible;
    
    std::map<std::string, std::string> m_tags;
};

}
