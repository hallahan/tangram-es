#pragma once

#include <vector>
#include <set>

#include "element.h"
#include "node.h"

namespace OSM {

class Way : public Element {

public:
    explicit Way(const long _id, const std::string& _versionStr,
                 const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
                 const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr);

    void addNodeRef(long _refId);
    size_t linkNodes(const std::map<long, std::shared_ptr<Node>>& _nodes, const std::set<long>& _wayNodeIds);
    bool isClosed() { return m_isClosed; }

private:
    void checkIfClosed();

    std::vector<long> m_nodeRefs; // all refs
    std::vector<long> m_unlinkedNodeRefs; // unlinked refs
    std::vector<std::shared_ptr<Node>> m_linkedNodes; // list of linked node objects
    bool m_isClosed;

};

}
