#include "node.h"

namespace OSM {

Node::Node(const long _id, const std::string& _latStr, const std::string& _lonStr, const std::string& _versionStr,
           const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
           const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr ) : 
Element(_id, _versionStr, _timestampStr, _changesetStr, _uidStr, _userStr, _actionStr, _visibleStr),
m_lat(std::stod(_latStr)),
m_lon(std::stod(_lonStr)) {

}

}
