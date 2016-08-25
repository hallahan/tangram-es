#pragma once

#include <vector>
#include <set>

#include "element.h"
#include "node.h"

namespace OSM {

class Way : public Element {

public:
    explicit Way(const long _id, const long _version,
                 const std::string& _timestamp, const long _changeset, const long _uid,
                 const std::string& _user, const std::string& _action, const std::string& _visible);

    void addNodeRef(long _refId);
    size_t linkNodes(const std::map<long, std::shared_ptr<Node>>& _nodes, const std::set<long>& _wayNodeIds);
    bool isClosed() { return m_isClosed; }
    const std::vector<std::shared_ptr<Node>>& nodes() const { return m_linkedNodes; }

private:
    void checkIfClosed();

    std::vector<long> m_nodeRefs; // all refs
    std::vector<long> m_unlinkedNodeRefs; // unlinked refs
    std::vector<std::shared_ptr<Node>> m_linkedNodes; // list of linked node objects
    bool m_isClosed;

};

}
