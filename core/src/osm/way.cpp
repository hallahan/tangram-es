#include "way.h"

namespace OSM {

Way::Way(const long _id, const long _version,
         const std::string& _timestamp, const long _changeset, const long _uid,
         const std::string& _user, const std::string& _action, const std::string& _visible) :
Element(_id, _version, _timestamp, _changeset, _uid, _user, _action, _visible) {
    
}

void Way::addNodeRef(long _refId) {
    m_nodeRefs.push_back(_refId);
}

size_t Way::linkNodes(const std::map<long, std::shared_ptr<Node>>& _nodes, const std::set<long>& _wayNodeIds) {
    // first check if the way is closed before doing this processing...
    checkIfClosed();

    for (auto const& refId : m_nodeRefs) {
        auto search = _nodes.find(refId);
        // if we have corresponding node
        if (search != _nodes.end()) {
            m_linkedNodes.push_back(search->second);
        }
        // if we do not have corresponding node
        else {
            m_unlinkedNodeRefs.push_back(refId);
        }
    }
    return m_unlinkedNodeRefs.size();
}

void Way::checkIfClosed() {
    if (m_nodeRefs.front() == m_nodeRefs.back()) {
        m_isClosed = true;
    } else {
        m_isClosed = false;
    }
}

}
