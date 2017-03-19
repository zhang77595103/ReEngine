
#ifndef REENGINE_EDGE_H
#define REENGINE_EDGE_H

class Edge;
using PEdge = Edge*;
class Node;
using PNode = Node*;


class Edge {
public:
    char getValue() const { return value; }
    void setValue(char value) { Edge::value = value; }

    const PNode getTo() const { return to; }
    void setTo(PNode to) { Edge::to = to; }


private:
    char value;
    PNode to;

};


#endif //REENGINE_EDGE_H
