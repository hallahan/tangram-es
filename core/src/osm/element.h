#pragma once

namespace OSM {

class Element {

public:

    void addParsedTag(const std::string k, const std::string v);
    void addNodeRef(long id);
    
protected:
    
};

}
