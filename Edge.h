#ifndef REENGINE_EDGE_H
#define REENGINE_EDGE_H

template <typename PNodeType>
class Edge {
public:
    char getValue() const { return value; }
    void setValue(char value) { Edge::value = value; }

    const PNodeType getTo() const { return to; }
    void setTo(PNodeType to) { Edge::to = to; }


private:
    char value;
    PNodeType to;

};


#endif //REENGINE_EDGE_H
