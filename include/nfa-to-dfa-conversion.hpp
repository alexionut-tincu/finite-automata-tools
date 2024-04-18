#ifndef NFA_TO_DFA_CONVERSION_HPP
#define NFA_TO_DFA_CONVERSION_HPP

#include "deterministic-fa.hpp"
#include "nondeterministic-fa.hpp"

DeterministicFA NFAtoDFA(const NonDeterministicFA &nfa);

#endif // NFA_TO_DFA_CONVERSION_HPP