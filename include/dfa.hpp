#ifndef DFA_HPP
#define DFA_HPP

#include <istream>
#include <set>
#include <string>
#include <unordered_map>

class DFA {
public:
	DFA();
	~DFA();

	void SetStatesCount(const size_t states);

	void AddState(const int state);

	void SetStateFinal(const int state);

	void SetInitState(const int state);

	void AddTransition(const int start_state,
			   const char letter,
			   const int end_state);

	bool AcceptWord(const std::string &word);

	void ReadDFA(std::istream &stream);

private:
	size_t states_count_;
	std::set<int> states_;
	std::set<int> final_states_;
	int init_state_;
	std::unordered_map<int, std::unordered_map<char, int>>
		transition_function_;
};

#endif //DFA_HPP