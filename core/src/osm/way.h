#pragma once

#include "element.h"

namespace OSM {

class Way : public Element {

public:
    explicit Way(const long _id, const std::string& _versionStr,
                 const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
                 const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr);
private:
    
};

}
