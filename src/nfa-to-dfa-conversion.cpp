#include "nfa-to-dfa-conversion.hpp"

#include <queue>

DeterministicFA NFAtoDFA(const NonDeterministicFA &nfa)
{
	DeterministicFA dfa;

	std::set<std::set<int>> dfa_states;
	std::map<std::set<int>, int> dfa_states_mapping;
	int map_idx = 0;
	std::queue<std::set<int>> dfa_states_queue;

	std::set<int> initial_state = {nfa.GetInitState()};
	dfa_states.insert(initial_state);
	dfa_states_mapping[initial_state] = map_idx++;
	dfa.SetInitState(dfa_states_mapping[initial_state]);

	dfa_states_queue.push(initial_state);

	while (dfa_states_queue.empty() == false) {
		std::set<int> current_states = dfa_states_queue.front();
		dfa_states_queue.pop();

		for (char letter = 'a'; letter <= 'z'; ++letter) {
			std::set<int> next_states;
			
			for (int state : current_states) {
				std::set<int> next_states_tmp = nfa.GetTransitionDestinations(state, letter);
				next_states.insert(next_states_tmp.begin(), next_states_tmp.end());
			}

			if (next_states.empty() == true) {
				continue;
			}

			if (dfa_states.count(next_states) == 0) {
				dfa_states.insert(next_states);
				dfa_states_mapping[next_states] = map_idx++;
				dfa_states_queue.push(next_states);
			}
			
			dfa.AddTransition(dfa_states_mapping[current_states],
					  letter,
					  dfa_states_mapping[next_states]);
		}
	}

	// add all states in dfa.states_
	for (const std::set<int> &dfa_state : dfa_states) {
		for (int state : dfa_state) {
			dfa.AddState(dfa_states_mapping[dfa_state]);
		}
	}

	for (const std::set<int> &dfa_state : dfa_states) {
		for (int nfa_state : dfa_state) {
			if (nfa.IsFinal(nfa_state) == true) {
				dfa.SetStateFinal(dfa_states_mapping[dfa_state]);
			}
		}
	}

	dfa.SetStatesCount(dfa_states.size());

	return dfa;
}