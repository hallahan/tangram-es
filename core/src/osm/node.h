#pragma once

#include "element.h"
#include "glm/glm.hpp"

namespace OSM {

class Node : public Element {

public:
    explicit Node(const long _id, const double _lat, const double _lon, const long _version,
                  const std::string& _timestamp, const long _changeset, const long _uid,
                  const std::string& _user, const std::string& _action, const std::string& _visible);

    glm::dvec2 lonLat() const { return glm::dvec2(m_lon, m_lat); }

private:
    double m_lat;
    double m_lon;
};

}
