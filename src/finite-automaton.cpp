#include "finite-automaton.hpp"

FiniteAutomaton::FiniteAutomaton() {};

FiniteAutomaton::~FiniteAutomaton() {};

void FiniteAutomaton::SetStatesCount(const size_t states)
{
	this->states_count_ = states;
}

void FiniteAutomaton::AddState(const int state)
{
	this->states_.insert(state);
}

void FiniteAutomaton::SetStateFinal(const int state)
{
	this->final_states_.insert(state);
}

void FiniteAutomaton::SetInitState(const int state)
{
	this->init_state_;
}