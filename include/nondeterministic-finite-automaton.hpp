#ifndef NONDETERMINISTIC_FINITE_AUTOMATON_HPP
#define	NONDETERMINISTIC_FINITE_AUTOMATON_HPP

#include "finite-automaton.hpp"
#include <istream>
#include <map>
#include <set>
#include <string>

class NonDeterministicFiniteAutomaton : public FiniteAutomaton {
public:
	NonDeterministicFiniteAutomaton();

	void AddTransition(const int start_state,
			   const char letter,
			   const int end_state);

	bool AcceptWord(const std::string &word);

	void ReadNFA(std::istream &stream);

private:
	// TODO: use umap for better performance but needed custom hash func
	std::map<std::pair<int, char>, std::set<int>> transition_function_;
};

#endif // "NONDETERMINISTIC_FINITE_AUTOMATON_HPP"