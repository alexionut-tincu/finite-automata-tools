#include "nondeterministic-fa.hpp"

NonDeterministicFA::NonDeterministicFA() {};

void NonDeterministicFA::AddTransition(const int start_state,
						     const char letter,
						     const int end_state)
{
	transition_function_[std::make_pair(start_state, letter)].insert(end_state);
	transitions_list_[start_state].insert(letter);
}

std::set<int> NonDeterministicFA::GetTransitionDestinations
	(const int state, const char letter) const
{
	if (transition_function_.count(std::make_pair(state, letter)) > 0) {
		return transition_function_.at(std::make_pair(state, letter));
	}
	return std::set<int>();
}

std::map<std::pair<int, char>, std::set<int>> NonDeterministicFA::GetTransitionFunction() const
{
	return transition_function_;
}

bool NonDeterministicFA::AcceptWord(const std::string &word)
{
	std::set<int> current_states = {init_state_};

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

void NonDeterministicFA::ReadNFA(std::istream &stream)
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

void NonDeterministicFA::PrintNFA(std::ostream &stream)
{
	stream << states_count_ << std::endl;

	for (int state : states_) {
		stream << state << " ";
	}
	stream << std::endl;

	stream << transition_function_.size() << std::endl;

	for (const auto &transition : transition_function_) {
		stream << transition.first.first << " "
		       << transition.first.second << " "
		       << transition.second.size() << " ";
		for (int state : transition.second) {
			stream << state << " ";
		}
		stream << std::endl;
	}

	stream << init_state_ << std::endl;

	stream << final_states_.size() << std::endl;

	for (int state : final_states_) {
		stream << state << " ";
	}
	stream << std::endl;
}