#ifndef LAMBDA_NFA_HPP
#define LAMBDA_NFA_HPP

#include "finite-automaton.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>

class LambdaNFA : public FiniteAutomaton {
public:
	LambdaNFA();

	void AddTransition(const int start_state,
			   const char letter,
			   const int end_state);

	std::set<int> GetTransitionDestinations(const int state,
						const char letter) const;

	void GenerateLambdaClosures();

	bool AcceptWord(const std::string &word);

	void ReadLambdaNFA(std::istream &stream);

	void PrintLambdaNFA(std::ostream &stream);

private:
	// TODO: use umap for better performance but needed custom hash func
	std::map<std::pair<int, char>, std::set<int>> transition_function_;
	std::map<int, std::set<int>> lambda_closures_;
};

#endif // LAMBDA_NFA_HPP