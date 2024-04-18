#include "deterministic-finite-automaton.hpp"

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton() {};

void DeterministicFiniteAutomaton::AddTransition(const int start_state,
						 const char letter,
						 const int end_state)
{
	transition_function_[std::make_pair(start_state, letter)] = end_state;
}

bool DeterministicFiniteAutomaton::AcceptWord(const std::string &word)
{
	int current_state = this->init_state_;

	for (char letter : word) {
		std::pair<int, char> transition = std::make_pair(current_state, letter);
		if (transition_function_.count(transition) == 0) {
			return false;
		}

		current_state = transition_function_[transition];
	}

	return true;
}

void DeterministicFiniteAutomaton::ReadDFA(std::istream &stream)
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
		transition_function_[std::make_pair(start_state, letter)] = end_state;
	}

	stream >> this->init_state_;

	size_t final_states_count;
	stream >> final_states_count;

	for (size_t i = 0; i < final_states_count; ++i) {
		int state;
		stream >> state;
		final_states_.insert(state);
	}
}