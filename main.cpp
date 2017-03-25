#include <iostream>
#include "NFA.h"
#include "DFA.h"

int main() {
    MemPool::Init();

    NFA nfa("(ab|cd)*ef?");
    nfa.BFSPrint();
    printf("----------------------------------\n");
    DFA dfa(nfa.getSegment());
    dfa.BFSPrint();

    MemPool::Destroy();
    return 0;
}