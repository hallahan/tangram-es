#include "node.h"

namespace OSM {

Node::Node(const long _id, const double _lat, const double _lon, const long _version,
           const std::string& _timestamp, const long _changeset, const long _uid,
           const std::string& _user, const std::string& _action, const std::string& _visible) :
Element(_id, _version, _timestamp, _changeset, _uid, _user, _action, _visible),
m_lat(_lat),
m_lon(_lon) {

}

}
