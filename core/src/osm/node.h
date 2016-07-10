#pragma once

#include "element.h"
#include "glm/glm.hpp"

namespace OSM {

class Node : public Element {

public:
    explicit Node(const long _id, const std::string& _latStr, const std::string& _lonStr, const std::string& _versionStr,
                  const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
                  const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr);

    glm::dvec2 lonLat() const { return glm::dvec2(m_lon, m_lat); }

private:
    double m_lat;
    double m_lon;
};

}
