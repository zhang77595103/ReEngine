#ifndef REENGINE_NODE_H
#define REENGINE_NODE_H

#include <map>
#include <vector>

#include "Edge.h"

enum {
    CONCATENATION = -1,
    ALTERNATION = -2,
    QUESTION = -3,
    CLOSURE = -4,
    PLUS = -5,
    POINT = -6,
    EPSILON = -7
};

class NFA_Node;
using Ptr_NFA_Node = NFA_Node*;
using Ptr_NFA_Node_Edge = Edge<Ptr_NFA_Node>*;

class NFA_Node {
public:

    NFA_Node() :id(counter++), isFinished(false) { }
    NFA_Node(const NFA_Node &)= delete;
    ~NFA_Node()= default;

    int getId() const { return id; }

    // get all edges
    const std::map<char, std::vector<Ptr_NFA_Node_Edge>> &getEdgeList()
    const { return edgeList; }

    // get edges for specific character
    std::vector<Ptr_NFA_Node_Edge> &getEdgeListAt(char ch) {
        if(edgeList.find(ch) == edgeList.cend())
            edgeList.insert({ch, std::vector<Ptr_NFA_Node_Edge>()});
        return edgeList[ch];
    }

    bool isIsFinished() const { return isFinished; }
    void setIsFinished(bool isFinished) { NFA_Node::isFinished = isFinished; }
private:
    static int counter;

    int id;
    std::map<char, std::vector<Ptr_NFA_Node_Edge>> edgeList;
    bool isFinished;
};


class NFA_Segment {
public:
    NFA_Segment(const Ptr_NFA_Node headNode, const Ptr_NFA_Node tailNode)
            :headNode(headNode), tailNode(tailNode) {}

    const Ptr_NFA_Node getHeadNode() const { return headNode; }
    const Ptr_NFA_Node getTailNode() const { return tailNode; }

private:
    Ptr_NFA_Node headNode;
    Ptr_NFA_Node tailNode;
};

using Ptr_NFA_Segment = NFA_Segment*;

#endif //REENGINE_NODE_H
