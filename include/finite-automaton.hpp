#ifndef FINITE_AUTOMATON_HPP
#define FINITE_AUTOMATON_HPP

#include <istream>
#include <set>
#include <stddef.h>

class FiniteAutomaton {
public:
	FiniteAutomaton();
	virtual ~FiniteAutomaton();

	void SetStatesCount(const size_t states);

	void AddState(const int state);

	void SetStateFinal(const int state);

	void SetInitState(const int state);

protected:
	int states_count_;
	std::set<int> states_;
	std::set<int> final_states_;
	int init_state_;
};

#endif //FINITE_AUTOMATON_HPP