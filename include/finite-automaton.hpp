#ifndef FINITE_AUTOMATON_HPP
#define FINITE_AUTOMATON_HPP

#include <istream>
#include <set>
#include <stddef.h>
#include <unordered_map>

class FiniteAutomaton {
public:
	FiniteAutomaton();
	virtual ~FiniteAutomaton();

	void SetStatesCount(const size_t states);

	void AddState(const int state);

	void SetStateFinal(const int state);

	bool IsFinal(const int state) const;

	void SetInitState(const int state);

	int GetInitState() const;

protected:
	int states_count_;
	std::set<int> states_;
	std::unordered_map<int, std::set<char>> transitions_list_;
	std::set<int> final_states_;
	int init_state_;
};

#endif //FINITE_AUTOMATON_HPP