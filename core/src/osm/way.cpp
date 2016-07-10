#include "way.h"

namespace OSM {

Way::Way(const long _id, const std::string& _versionStr,
         const std::string& _timestampStr, const std::string& _changesetStr, const std::string& _uidStr,
         const std::string& _userStr, const std::string& _actionStr, const std::string& _visibleStr) :
Element(_id, _versionStr, _timestampStr, _changesetStr, _uidStr, _userStr, _actionStr, _visibleStr) {
    
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
