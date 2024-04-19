#include "deterministic-fa.hpp"

DeterministicFA::DeterministicFA() {};

void DeterministicFA::AddTransition(const int start_state,
						 const char letter,
						 const int end_state)
{
	transition_function_[std::make_pair(start_state, letter)] = end_state;
	transitions_list_[start_state].insert(letter);
}

std::map<std::pair<int, char>, int> DeterministicFA::GetTransitionFunction() const
{
	return transition_function_;
}

bool DeterministicFA::AcceptWord(const std::string &word)
{
	int current_state = init_state_;

	for (char letter : word) {
		std::pair<int, char> transition = std::make_pair(current_state, letter);
		if (transition_function_.count(transition) == 0) {
			return false;
		}

		current_state = transition_function_[transition];
	}

	return true;
}

void DeterministicFA::ReadDFA(std::istream &stream)
{
	stream >> states_count_;

	for (size_t i = 0; i < states_count_; ++i) {
		int state;
		stream >> state;
		states_.insert(state);
	}

	size_t transitions_count;
	stream >> transitions_count;

	for (size_t i = 0; i < transitions_count; ++i) {
		int start_state, end_state;
		char letter;
		stream >> start_state >> end_state >> letter;
		AddTransition(start_state, letter, end_state);
	}

	stream >> init_state_;

	size_t final_states_count;
	stream >> final_states_count;

	for (size_t i = 0; i < final_states_count; ++i) {
		int state;
		stream >> state;
		final_states_.insert(state);
	}
}

void DeterministicFA::PrintDFA(std::ostream &stream)
{
	stream << states_count_ << std::endl;

	for (int state : states_) {
		stream << state << " ";
	}
	stream << std::endl;

	stream << transition_function_.size() << std::endl;

	for (const auto &transition : transition_function_) {
		stream << transition.first.first << " "
		       << transition.second << " "
		       << transition.first.second << std::endl;
	}

	stream << init_state_ << std::endl;

	stream << final_states_.size() << std::endl;

	for (int state : final_states_) {
		stream << state << " ";
	}
	stream << std::endl;
}