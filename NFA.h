#ifndef REENGINE_NFA_H
#define REENGINE_NFA_H

#include <string>
#include "MemPool.h"
#include "Nodes.h"

class NFA {

public:
    NFA(const std::string& pattern)
        : pNodes(nullptr){
        construct(pattern);
    }

    bool match(const std::string& target);

    void BFSPrint(int size = 100);

    ~NFA(){ if(pNodes != nullptr)   delete  pNodes; }

private:

    void construct(const std::string &pattern);

    void re2post(const std::string &pattern, std::string &postRe);

    void postRe2nfa(const std::string &postRe);

private:
    PNodes pNodes;

    MemPool pool;
};

#endif //REENGINE_NFA_H
