
#ifndef REENGINE_MEMPOOL_H
#define REENGINE_MEMPOOL_H


#include <cstdlib>
#include "Node.h"
#include "Edge.h"
#include "Nodes.h"

class MemPool {
private:
    const static int SIZE = 100;
    PNode nodePool = nullptr;
    PEdge edgePool = nullptr;

    int nodePos = 0;
    int edgePos = 0;

public:
    MemPool() {
        nodePool = new Node[SIZE];
        edgePool = new Edge[SIZE];
    }

    PNode giveMeNode(){
        if(nodePos == SIZE){
            printf("Node Pool Out Of Memory!\n");
            exit(0);
        }
        return &nodePool[nodePos++];
    }

    PEdge giveMeEdge(char value, PNode to){
        if(edgePos == SIZE){
            printf("Edge Pool Out Of Memory!\n");
            exit(0);
        }

        edgePool[edgePos].setValue(value);
        edgePool[edgePos].setTo(to);
        return &edgePool[edgePos++];
    }

    ~MemPool(){
        delete[] nodePool;
        delete[] edgePool;
    }
};

#endif //REENGINE_MEMPOOL_H
