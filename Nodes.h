
#ifndef REENGINE_NOTES_H
#define REENGINE_NOTES_H

#include "Node.h"

class Nodes;
using PNodes = Nodes*;


class Nodes {
public:
    Nodes(const PNode headNode, const PNode tailNode) :headNode(headNode), tailNode(tailNode) {}

    const PNode getHeadNode() const { return headNode; }
    const PNode getTailNode() const { return tailNode; }

private:
    PNode headNode;
    PNode tailNode;
};


#endif //REENGINE_NOTES_H
