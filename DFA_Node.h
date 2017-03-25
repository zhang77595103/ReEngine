#ifndef REENGINE_NODESET_H
#define REENGINE_NODESET_H

#include <vector>

#include "Edge.h"
#include "NFA_Node.h"


class DFA_Node;
using Ptr_DFA_Node = DFA_Node*;
using Ptr_DFA_Node_Edge = Edge<Ptr_DFA_Node>*;
using Ptr_NFA_Node_Set = std::vector<Ptr_NFA_Node>;

class DFA_Node {
private:
    static int counter;

    Ptr_NFA_Node_Set set;
    int id;
    std::map<char, Ptr_DFA_Node_Edge> edgeList;
    bool isFinished;

public:
    DFA_Node(): id(counter++), isFinished(false){}

    const Ptr_NFA_Node_Set &getSet() const { return set; }
    void setNfaNodeSet(const Ptr_NFA_Node_Set &nfaNodeSet) { DFA_Node::set = nfaNodeSet; }

    int getId() const { return id; }

    std::map<char, Ptr_DFA_Node_Edge> &getEdgeList() { return edgeList; }

    bool isIsFinished() const { return isFinished; }

    void setIsFinished(bool isFinished) { DFA_Node::isFinished = isFinished; }
};

#endif //REENGINE_NODESET_H
