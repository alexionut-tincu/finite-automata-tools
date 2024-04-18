#include "finite-automaton.hpp"

FiniteAutomaton::FiniteAutomaton() {};

FiniteAutomaton::~FiniteAutomaton() {};

void FiniteAutomaton::SetStatesCount(const size_t states)
{
	states_count_ = states;
}

void FiniteAutomaton::AddState(const int state)
{
	states_.insert(state);
}

void FiniteAutomaton::SetStateFinal(const int state)
{
	final_states_.insert(state);
}

bool FiniteAutomaton::IsFinal(const int state) const
{
	return final_states_.count(state) > 0;
}

void FiniteAutomaton::SetInitState(const int state)
{
	init_state_ = state;
}

int FiniteAutomaton::GetInitState() const
{
	return init_state_;
}