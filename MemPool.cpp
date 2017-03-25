#include "MemPool.h"


Ptr_NFA_Node MemPool::nfaNodePool;
Ptr_DFA_Node MemPool::dfaNodePool;
Ptr_NFA_Node_Edge MemPool::nfaEdgePool;
Ptr_DFA_Node_Edge MemPool::dfaEdgePool;

int MemPool::nfaNodePos = 0;
int MemPool::dfaNodePos = 0;
int MemPool::nfaEdgePos = 0;
int MemPool::dfaEdgePos = 0;

void MemPool::Init() {
    nfaNodePool = new NFA_Node[SIZE];
    dfaNodePool = new DFA_Node[SIZE];
    nfaEdgePool = new Edge<Ptr_NFA_Node>[SIZE];
    dfaEdgePool = new Edge<Ptr_DFA_Node>[SIZE];
}

Ptr_NFA_Node MemPool::Give_Me_NFA_Node(){
    if(nfaNodePos == SIZE){
        printf("NFA_Node Pool Out Of Memory!\n");
        exit(0);
    }
    return &nfaNodePool[nfaNodePos++];
}

Ptr_DFA_Node MemPool::Give_Me_DFA_Node(){
    if(dfaNodePos == SIZE){
        printf("DFA_Node Pool Out Of Memory!\n");
        exit(0);
    }

    return &dfaNodePool[dfaNodePos++];
}

Ptr_NFA_Node_Edge MemPool::Give_Me_NFA_Edge(char value, Ptr_NFA_Node to){
    if(nfaEdgePos == SIZE){
        printf("NFA_Edge Pool Out Of Memory!\n");
        exit(0);
    }

    nfaEdgePool[nfaEdgePos].setValue(value);
    nfaEdgePool[nfaEdgePos].setTo(to);
    return &nfaEdgePool[nfaEdgePos++];
}

Ptr_DFA_Node_Edge MemPool::Give_Me_DFA_Edge(char value, Ptr_DFA_Node to) {
    if(dfaEdgePos == SIZE){
        printf("DFA_Edge Pool Out Of Memory!\n");
        exit(0);
    }

    dfaEdgePool[dfaEdgePos].setValue(value);
    dfaEdgePool[dfaEdgePos].setTo(to);
    return &dfaEdgePool[dfaEdgePos++];

}

void MemPool::Destroy(){
    delete[] nfaNodePool;
    delete[] dfaNodePool;
    delete[] nfaEdgePool;
    delete[] dfaEdgePool;
}
