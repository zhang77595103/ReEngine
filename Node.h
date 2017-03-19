#ifndef REENGINE_NODE_H
#define REENGINE_NODE_H


#include <map>
#include <vector>

class Edge;
using PEdge = Edge*;
class Node;
using PNode = Node*;


class Node {
public:
    Node() :id(counter++), isFinished(false) { }

    Node(const Node &)= delete;

    int getId() const { return id; }
    void setId(int id) { Node::id = id; }

    std::vector<PEdge> &getEdgeListAt(char ch) {
        if(edgeList.find(ch) == edgeList.cend()){
            edgeList.insert({ch, std::vector<PEdge>()});
        }
        return edgeList[ch];
    }

    const std::map<char, std::vector<PEdge>> &getEdgeList() const { return edgeList; }

    bool isIsFinished() const { return isFinished; }
    void setIsFinished(bool isFinished) { Node::isFinished = isFinished; }
private:
    static int counter;
    int id;
    std::map<char, std::vector<PEdge>> edgeList;
    bool isFinished = false;
};


#endif //REENGINE_NODE_H
