#include "lambda-nfa.hpp"
#include <queue>

#define LAMBDA '*'

LambdaNFA::LambdaNFA() {};

void LambdaNFA::AddTransition(const int start_state,
			      const char letter,
			      const int end_state)
{
	transition_function_[std::make_pair(start_state, letter)].insert(end_state);
}

std::set<int> LambdaNFA::GetTransitionDestinations(const int state,
						    const char letter) const
{
	if (transition_function_.count(std::make_pair(state, letter)) > 0) {
		return transition_function_.at(std::make_pair(state, letter));
	}
	return std::set<int>();
}

void LambdaNFA::GenerateLambdaClosures()
{
	for (int state : states_) {
		std::set<int> closure;
		std::queue<int> queue;
		queue.push(state);

		while (queue.empty() == false) {
			int current_state = queue.front();
			queue.pop();
			closure.insert(current_state);

			for (int next_state : GetTransitionDestinations(current_state, LAMBDA)) {
				if (closure.count(next_state) == 0) {
					queue.push(next_state);
				}
			}

		}

		lambda_closures_[state] = closure;
	}
}

void LambdaNFA::ReadLambdaNFA(std::istream &stream)
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

	GenerateLambdaClosures();
}

void LambdaNFA::PrintLambdaNFA(std::ostream &stream)
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
