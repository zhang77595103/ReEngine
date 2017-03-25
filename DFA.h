#ifndef REENGINE_DFA_H
#define REENGINE_DFA_H

#include "DFA_Node.h"

using Hash = unsigned long;

class DFA {
public:
    DFA(const Ptr_NFA_Segment nfaSegment){
        finishNumber = nfaSegment->getTailNode()->getId();
        construct(nfaSegment->getHeadNode());
    }

    void BFSPrint(unsigned int size = 64);

private:
    void construct(const Ptr_NFA_Node ptr_nfa_node);

    void epsilonClosure(Ptr_NFA_Node_Set& set);

    Hash hash(const Ptr_NFA_Node_Set&);

private:
    std::map<unsigned long, Ptr_DFA_Node > dfaTable;

    Ptr_DFA_Node startState;

    int finishNumber;
};


#endif //REENGINE_DFA_H
