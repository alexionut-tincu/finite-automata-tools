#include "nondeterministic-finite-automaton.hpp"

NonDeterministicFiniteAutomaton::NonDeterministicFiniteAutomaton() {};

void NonDeterministicFiniteAutomaton::AddTransition(const int start_state,
						     const char letter,
						     const int end_state)
{
	transition_function_[std::make_pair(start_state, letter)].insert(end_state);
}

bool NonDeterministicFiniteAutomaton::AcceptWord(const std::string &word)
{
	std::set<int> current_states = {this->init_state_};

	for (char letter : word) {
		std::set<int> next_states;
		for (int state : current_states) {
			std::pair<int, char> transition = std::make_pair(state, letter);
			if (transition_function_.count(transition) == 0) {
				continue;
			}

			for (int next_state : transition_function_[transition]) {
				next_states.insert(next_state);
			}
		}

		current_states = next_states;
	}

	for (int state : current_states) {
		if (final_states_.count(state) > 0) {
			return true;
		}
	}

	return false;
}

void NonDeterministicFiniteAutomaton::ReadNFA(std::istream &stream)
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
		transition_function_[std::make_pair(start_state, letter)].insert(end_state);
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