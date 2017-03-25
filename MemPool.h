
#ifndef REENGINE_MEMPOOL_H
#define REENGINE_MEMPOOL_H

#include <cstdlib>

#include "NFA_Node.h"
#include "Edge.h"
#include "DFA_Node.h"

class MemPool {
private:
    const static int SIZE = 100;
    static Ptr_NFA_Node nfaNodePool;
    static Ptr_DFA_Node dfaNodePool;
    static Ptr_NFA_Node_Edge nfaEdgePool;
    static Ptr_DFA_Node_Edge dfaEdgePool;

    static int nfaNodePos;
    static int dfaNodePos;
    static int nfaEdgePos;
    static int dfaEdgePos;

public:
    static void Init();

    static Ptr_NFA_Node Give_Me_NFA_Node();
    static Ptr_DFA_Node Give_Me_DFA_Node();

    static Ptr_NFA_Node_Edge Give_Me_NFA_Edge(char value, Ptr_NFA_Node to);
    static Ptr_DFA_Node_Edge Give_Me_DFA_Edge(char value, Ptr_DFA_Node to);

    static void Destroy();
};

#endif //REENGINE_MEMPOOL_H
