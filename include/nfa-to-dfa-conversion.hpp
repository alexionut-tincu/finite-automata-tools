#ifndef NFA_TO_DFA_CONVERSION_HPP
#define NFA_TO_DFA_CONVERSION_HPP

#include "deterministic-finite-automaton.hpp"
#include "nondeterministic-finite-automaton.hpp"

DeterministicFiniteAutomaton NFAtoDFA(const NonDeterministicFiniteAutomaton &nfa);

#endif // NFA_TO_DFA_CONVERSION_HPP