#include <iostream>
#include <queue>
#include <stack>
#include "NFA.h"

enum {
    CONCATENATION = -1,
    ALTERNATION = -2,
    CLOSURE = -3,

    EPSILON = -4
};

void NFA::construct(const std::string &pattern){
    std::string postRe;
    re2post(pattern, postRe);
    postRe2nfa(postRe);
}

void NFA::re2post(const std::string &pattern, std::string &postRe){
    std::stack<std::pair<int, int>> bracketStack;
    int numberOfAtom = 0;
    int numberOfOr = 0;

    for(auto ch : pattern){
        switch (ch){
            case '(':
                if(numberOfAtom > 1){
                    --numberOfAtom;
                    postRe += CONCATENATION;
                }

                bracketStack.push({numberOfAtom, numberOfOr});
                numberOfAtom = 0;
                numberOfOr = 0;
                break;
            case ')':{
                if(numberOfAtom > 1){
                    --numberOfAtom;
                    postRe += CONCATENATION;
                }
                while (numberOfOr){
                    --numberOfOr;
                    postRe += ALTERNATION;
                }

                auto temp = numberOfAtom;
                numberOfAtom = bracketStack.top().first;
                numberOfOr = bracketStack.top().second;
                bracketStack.pop();

                numberOfAtom = temp == 0 ? numberOfAtom : numberOfAtom + 1;
                break;
            }
            case '|':
                /**
                 *  the left side should of | should got no association with the right side,
                 *  so let numberOfAtom be zero rather than 1. But basically it's the same as
                 *
                 *  if(numberOfAtom > 1){
                 *      --numberOfAtom;
                 *      postRe += CONCATENATION;
                 *  }
                 *  --numberOfAtom;
                 *
                 */
                while (--numberOfAtom > 0){
                    postRe += CONCATENATION;
                }
                ++numberOfOr;
                break;
            default:
                if(numberOfAtom > 1){
                    --numberOfAtom;
                    postRe += CONCATENATION;
                }
                ++numberOfAtom;
                postRe += ch;
        }
    }
    if(numberOfAtom > 1){
        --numberOfAtom;
        postRe += CONCATENATION;
    }
    while (numberOfOr){
        --numberOfOr;
        postRe += ALTERNATION;
    }

#if 0
    for(auto ch : postRe){
        switch (ch){
            case CONCATENATION:
                std::cout << ".";
                break;
            case ALTERNATION:
                std::cout << '|';
                break;
            default:
                std::cout << ch;
        }
    }
    std::cout << std::endl;
#endif
}

void NFA::postRe2nfa(const std::string &postRe){
    std::stack<Nodes> nodesStack;
    for(auto ch : postRe){
        switch (ch){
            case CONCATENATION: {
                auto next = nodesStack.top();
                nodesStack.pop();
                auto previous = nodesStack.top();
                nodesStack.pop();

                previous.getTailNode()->getEdgeListAt(EPSILON).push_back(pool.giveMeEdge(EPSILON, next.getHeadNode()));
                nodesStack.push(Nodes(previous.getHeadNode(), next.getTailNode()));
                break;
            }
            case ALTERNATION: {
                auto next = nodesStack.top();
                nodesStack.pop();
                auto previous = nodesStack.top();
                nodesStack.pop();

                auto head = pool.giveMeNode();
                auto tail = pool.giveMeNode();
                head->getEdgeListAt(EPSILON).push_back(pool.giveMeEdge(EPSILON, previous.getHeadNode()));
                head->getEdgeListAt(EPSILON).push_back(pool.giveMeEdge(EPSILON, next.getHeadNode()));
                previous.getTailNode()->getEdgeListAt(EPSILON).push_back(pool.giveMeEdge(EPSILON, tail));
                next.getTailNode()->getEdgeListAt(EPSILON).push_back(pool.giveMeEdge(EPSILON, tail));
                nodesStack.push(Nodes(head, tail));
                break;
            }
            default:
                auto headNode = pool.giveMeNode();
                auto tailNode = pool.giveMeNode();
                headNode->getEdgeListAt(ch).push_back(pool.giveMeEdge(ch, tailNode));
                nodesStack.push(Nodes(headNode, tailNode));
        }
    }

    pNodes = new Nodes(nodesStack.top());
    pNodes->getTailNode()->setIsFinished(true);
}

bool NFA::match(const std::string& target){
    return false;
}

void NFA::BFSPrint(int size){
    char alreadyVisited[size];
    memset(alreadyVisited, 0, size);
    std::queue<PNode> toVisited;
    toVisited.push(pNodes->getHeadNode());
    while (true){
        if(toVisited.empty())   return;
        auto curNode = toVisited.front();
        toVisited.pop();

        if(alreadyVisited[curNode->getId()])  continue;

        alreadyVisited[curNode->getId()] = true;
        printf("Node %d: \n", curNode->getId());
        if(curNode->isIsFinished()){
            printf("\tFinish Node %d!\n", curNode->getId());
        }
        for(auto eachList : curNode->getEdgeList()){
            for(auto eachEdge : eachList.second){
                printf("\t -(%c)> %d\n",
                       eachEdge->getValue() == EPSILON ? '-' : eachEdge->getValue(),
                       eachEdge->getTo()->getId());
                toVisited.push(eachEdge->getTo());
            }
        }
    }
}


