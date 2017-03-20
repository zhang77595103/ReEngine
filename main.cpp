#include <iostream>
#include "NFA.h"

int main() {
    NFA nfa("(ab)+e.");
    nfa.BFSPrint();
    return 0;
}