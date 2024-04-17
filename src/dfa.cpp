#include "dfa.hpp"

DFA::DFA() {};

DFA::~DFA() {};

void DFA::SetStatesCount(const size_t states)
{
	this->states_count_ = states;
}

void DFA::AddState(const int state)
{
	this->states_.insert(state);
}

void DFA::SetStateFinal(const int state)
{
	this->final_states_.insert(state);
}

void DFA::SetInitState(const int state)
{
	this->init_state_ = state;
}

void DFA::AddTransition(const int start_state, const char letter, const int end_state)
{
	transition_function_[start_state][letter] = end_state;
}

bool DFA::AcceptWord(const std::string &word)
{
	int current_state = this->init_state_;

	for (char letter : word) {
		if (transition_function_[current_state].count(letter) == 0) {
			return false;
		}
		current_state = transition_function_[current_state][letter];
	}

	return (final_states_.count(current_state) > 0);
}

void DFA::ReadDFA(std::istream &stream)
{
	stream >> this->states_count_;

	for (size_t i = 0; i < this->states_count_; ++i) {
		int state;
		stream >> state;
		this->states_.insert(state);
	}

	size_t transitions_count;
	stream >> transitions_count;

	for (size_t i = 0; i < transitions_count; ++i) {
		int start_state, end_state;
		char letter;
		stream >> start_state >> end_state >> letter;
		this->transition_function_[start_state][letter] = end_state;
	}

	stream >> this->init_state_;

	size_t final_states_count;
	stream >> final_states_count;

	for (size_t i = 0; i < final_states_count; ++i) {
		int final_state;
		stream >> final_state;
		this->final_states_.insert(final_state);
	}
}