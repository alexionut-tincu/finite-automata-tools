#ifndef FINITE-AUTOMATON_HPP
#define FINITE-AUTOMATON_HPP

#include <istream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

class FiniteAutomaton {
public:
	FiniteAutomaton();
	virtual ~FiniteAutomaton();

	void SetStatesCount(const size_t states);

	void AddState(const int state);

	void SetStateFinal(const int state);

	void SetInitState(const int state);

private:
	size_t states_count_;
	std::set<int> states_;
	std::set<int> final_states_;
	int init_state_;
};

#endif //FINITE-AUTOMATON_HPP