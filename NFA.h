#ifndef REENGINE_NFA_H
#define REENGINE_NFA_H

#include <string>
#include "MemPool.h"
#include "NFA_Node.h"

class NFA {

public:
    NFA(const std::string& pattern)
        : segment(nullptr){
        construct(pattern);
    }



    void BFSPrint(unsigned int size = 64);

    ~NFA(){ if(segment != nullptr)   delete  segment; }

    const Ptr_NFA_Segment getSegment() const { return segment; }


private:

    void construct(const std::string &pattern);

    void re2post(const std::string &pattern, std::string &postRe);

    void postRe2nfa(const std::string &postRe);

private:
    Ptr_NFA_Segment segment;
};

#endif //REENGINE_NFA_H
