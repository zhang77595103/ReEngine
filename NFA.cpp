#include <iostream>
#include <queue>
#include <stack>
#include "NFA.h"


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
            case '?':
                postRe += QUESTION;
                break;
            case '*':
                postRe += CLOSURE;
                break;
            case '+':
                postRe += PLUS;
                break;
            case '.':
                ch = POINT;
                // drop
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

#if 1
    for(auto ch : postRe){
        switch (ch){
            case CONCATENATION:
                std::cout << "&";
                break;
            case ALTERNATION:
                std::cout << '|';
                break;
            case QUESTION:
                std::cout << '?';
                break;
            case CLOSURE:
                std::cout << '*';
                break;
            case PLUS:
                std::cout << '+';
                break;
            case POINT:
                std::cout << '.';
                break;
            default:
                std::cout << ch;
        }
    }
    std::cout << std::endl;
#endif
}

void NFA::postRe2nfa(const std::string &postRe){
    std::stack<NFA_Segment> nodesStack;
    for(auto ch : postRe){
        switch (ch){
            case CONCATENATION: {
                auto next = nodesStack.top();
                nodesStack.pop();
                auto previous = nodesStack.top();
                nodesStack.pop();

                previous.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, next.getHeadNode()));
                nodesStack.push(NFA_Segment(previous.getHeadNode(), next.getTailNode()));
                break;
            }
            case ALTERNATION: {
                auto next = nodesStack.top();
                nodesStack.pop();
                auto previous = nodesStack.top();
                nodesStack.pop();

                auto head = MemPool::Give_Me_NFA_Node();
                auto tail = MemPool::Give_Me_NFA_Node();
                head->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, previous.getHeadNode()));
                head->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, next.getHeadNode()));
                previous.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, tail));
                next.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, tail));
                nodesStack.push(NFA_Segment(head, tail));
                break;
            }
            case QUESTION:{
                auto& ref = nodesStack.top();
                auto head = MemPool::Give_Me_NFA_Node();
                auto tail = MemPool::Give_Me_NFA_Node();
                head->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, tail));
                head->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, ref.getHeadNode()));
                ref.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, tail));
                nodesStack.pop();
                nodesStack.push(NFA_Segment(head, tail));
                break;
            }
            case CLOSURE:{
                auto& ref = nodesStack.top();
                // for the original one : connect from tail back to head
                ref.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, ref.getHeadNode()));

                auto head = MemPool::Give_Me_NFA_Node();
                auto tail = MemPool::Give_Me_NFA_Node();
                head->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, tail));
                head->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, ref.getHeadNode()));
                ref.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, tail));
                nodesStack.pop();
                nodesStack.push(NFA_Segment(head, tail));
                break;
            }
            case PLUS:{
                auto& ref = nodesStack.top();
                // for the original one : connect from tail back to head
                ref.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, ref.getHeadNode()));

                auto head = MemPool::Give_Me_NFA_Node();
                auto tail = MemPool::Give_Me_NFA_Node();
                head->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, ref.getHeadNode()));
                ref.getTailNode()->getEdgeListAt(EPSILON).push_back(MemPool::Give_Me_NFA_Edge(EPSILON, tail));
                nodesStack.pop();
                nodesStack.push(NFA_Segment(head, tail));
                break;
            }
            default:
                auto headNode = MemPool::Give_Me_NFA_Node();
                auto tailNode = MemPool::Give_Me_NFA_Node();

                headNode->getEdgeListAt(ch).push_back(MemPool::Give_Me_NFA_Edge(ch, tailNode));
                nodesStack.push(NFA_Segment(headNode, tailNode));
        }
    }

    segment = new NFA_Segment(nodesStack.top());
    segment->getTailNode()->setIsFinished(true);
}

void NFA::BFSPrint(unsigned int size){
    char alreadyVisited[size];
    memset(alreadyVisited, 0, size);
    std::queue<Ptr_NFA_Node> toVisited;
    toVisited.push(segment->getHeadNode());
    while (true){
        if(toVisited.empty())   return;
        auto curNode = toVisited.front();
        toVisited.pop();

        if(alreadyVisited[curNode->getId()])  continue;

        alreadyVisited[curNode->getId()] = true;
        printf("NFA_Node %d: \n", curNode->getId());
        if(curNode->isIsFinished()){
            printf("\tFinish NFA_Node %d!\n", curNode->getId());
        }
        for(auto eachList : curNode->getEdgeList()){
            for(auto eachEdge : eachList.second){
                printf("\t -(%c)> %d\n",
                       eachEdge->getValue() == EPSILON ? '-' :
                       eachEdge->getValue() == POINT ? '.' :
                       eachEdge->getValue(),
                       eachEdge->getTo()->getId());
                toVisited.push(eachEdge->getTo());
            }
        }
    }
}


