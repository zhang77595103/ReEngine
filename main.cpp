#include <iostream>
#include "NFA.h"

int main() {
    NFA nfa("a(b|c|d)e");
    nfa.BFSPrint();
    return 0;
}