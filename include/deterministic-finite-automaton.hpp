#ifndef DETERMINISTIC_FINITE_AUTOMATON_HPP
#define DETERMINISTIC_FINITE_AUTOMATON_HPP

#include "finite-automaton.hpp"
#include <iostream>
#include <map>
#include <string>

class DeterministicFiniteAutomaton : public FiniteAutomaton {
public:
	DeterministicFiniteAutomaton();

	void AddTransition(const int start_state,
			   const char letter,
			   const int end_state);
		
	bool AcceptWord(const std::string &word);

	void ReadDFA(std::istream &stream);

	void PrintDFA(std::ostream &stream);

private:
	// TODO: use umap for better performance but needed custom hash func
	std::map<std::pair<int, char>, int> transition_function_;
};

#endif // DETERMINISTIC_FINITE_AUTOMATON_HPP