#include <cmath>
#include <queue>
#include "DFA.h"
#include "MemPool.h"

static bool isFinish;
void DFA::construct(const Ptr_NFA_Node ptr_nfa_node){
    Ptr_NFA_Node_Set set{ptr_nfa_node};
    epsilonClosure(set);
    Ptr_DFA_Node ptr_dfa_node = MemPool::Give_Me_DFA_Node();
    ptr_dfa_node->setIsFinished(isFinish);
    ptr_dfa_node->setNfaNodeSet(set);
    dfaTable.insert({hash(set), ptr_dfa_node});
    startState = ptr_dfa_node;

    std::queue<Ptr_DFA_Node> toVisit;
    toVisit.push(ptr_dfa_node);
    while (true){
        ptr_dfa_node = toVisit.front(); toVisit.pop();

        for(int ch = 0; ch < 128; ++ch){
            Ptr_NFA_Node_Set newSet;
            for(const auto &nfa : ptr_dfa_node->getSet()){
                auto &edges = nfa->getEdgeListAt(ch);
                for(const auto &edge : edges){
                    newSet.push_back(edge->getTo());
                }
            }
            if(newSet.size() != 0){
                epsilonClosure(newSet);
                auto hashValue = hash(newSet);
                if(dfaTable.find(hashValue) == dfaTable.cend()){
                    // an new state
                    Ptr_DFA_Node newDfa = MemPool::Give_Me_DFA_Node();
                    newDfa->setIsFinished(isFinish);
                    newDfa->setNfaNodeSet(newSet);
                    dfaTable.insert({hash(newSet), newDfa});

                    //connect
                    ptr_dfa_node->getEdgeList().insert(
                            {ch, MemPool::Give_Me_DFA_Edge(ch, newDfa)}
                    );

                    toVisit.push(newDfa);
                } else{
                    // the state exist already
                    ptr_dfa_node->getEdgeList().insert(
                            {ch, MemPool::Give_Me_DFA_Edge(ch, dfaTable.find(hashValue)->second)}
                    );
                }
            }
        }

        if(toVisit.empty()) break;
    }
}


void DFA::epsilonClosure(Ptr_NFA_Node_Set& set){
    isFinish = false;
    /*
     *  In fact it's just a dfs, but we do not need to record the visited node
     *  since the nfa is not cyclic using previous construction algorithm.
     */
    Ptr_NFA_Node_Set toVisited{set};
    set.clear();
    while (true){
        if(toVisited.size() == 0) break;
        auto curNode = toVisited.back(); toVisited.pop_back();
        set.push_back(curNode);
        if(curNode->getId() == finishNumber){
            isFinish = true;
        }
        for(auto each : curNode->getEdgeListAt(EPSILON)) {
            toVisited.push_back(each->getTo());
        }
    }
}

Hash DFA::hash(const Ptr_NFA_Node_Set& set){
    unsigned long hashCode = 0;
    for(const auto &each : set){
        hashCode += std::pow(2, each->getId());
    }
    return hashCode;
}



void DFA::BFSPrint(unsigned int size){
    char alreadyVisited[size];
    memset(alreadyVisited, 0, size);
    std::queue<Ptr_DFA_Node> toVisited;
    toVisited.push(startState);
    while (true){
        if(toVisited.empty())   return;
        auto curNode = toVisited.front();
        toVisited.pop();

        if(alreadyVisited[curNode->getId()])  continue;

        alreadyVisited[curNode->getId()] = true;
        printf("DFA_Node %d: \n", curNode->getId());
        if(curNode->isIsFinished()){
            printf("\tFinish NFA_Node %d!\n", curNode->getId());
        }
        for(auto each : curNode->getEdgeList()){
            printf("\t -(%c)> %d\n",
                   each.first == EPSILON ? '-' :
                   each.first == POINT ? '.' :
                   each.first,
                   each.second->getTo()->getId());
            toVisited.push(each.second->getTo());
        }
    }
}
