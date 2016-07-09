#include "way.h"

namespace OSM {

Way::Way(const long _id, const std::string& _versionStr,
         const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
         const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr) :
Element(_id, _versionStr, _timestampStr, _changesetStr, _uidStr, _userStr, _actionStr, _visibleStr) {
    
}

}
