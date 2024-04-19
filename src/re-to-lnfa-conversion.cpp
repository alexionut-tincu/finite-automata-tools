#include "re-to-lnfa-conversion.hpp"
#include <algorithm>

std::vector<std::string> TokenizeRE(const std::string &re)
{
	std::vector<std::string> tokens;
	std::string token;

	for (char c : re) {
		if (c == '(' || c == ')' || c == '*' || c == '|' || c == '.') {
			if (token.empty() == false) {
				tokens.push_back(token);
				token.clear();
			}
			tokens.push_back(std::string(1, c));
		} else {
			token += c;
		}
	}

	if (token.empty() == false) {
		tokens.push_back(token);
	}

	return tokens;
}

void ApplyOperator(const std::string &op, std::stack<LambdaNFA> &lnfas_stack, int &idx)
{
	if (op == "*") {
		if (lnfas_stack.size() > 0) {
			LambdaNFA lnfa = lnfas_stack.top();
			lnfas_stack.pop();

			lnfa.AddTransition(idx, LAMBDA, lnfa.GetInitState());
			lnfa.AddTransition(idx, LAMBDA, idx + 1);
			int lnfa_end = lnfa.GetAllStates().size() - 1;
			lnfa.AddTransition(lnfa_end, LAMBDA, lnfa.GetInitState());
			lnfa.AddTransition(lnfa_end, LAMBDA, idx + 1);
			lnfa.AddState(idx);
			lnfa.SetInitState(idx);
			lnfa.AddState(idx + 1);
			lnfa.SetStateFinal(idx + 1);
			lnfa.SetStatesCount(lnfa.GetAllStates().size());
			idx += 2;

			lnfas_stack.push(lnfa);
		}
	} else if (op == "|") {
		if (lnfas_stack.size() > 1) {
			LambdaNFA lnfa1 = lnfas_stack.top();
			lnfas_stack.pop();
			LambdaNFA lnfa2 = lnfas_stack.top();
			lnfas_stack.pop();

			for (int state : lnfa2.GetAllStates()) {
				lnfa1.AddState(state);
			}

			for (const auto &transition : lnfa2.GetTransitionFunction()) {
				int end_state = *transition.second.begin();
				lnfa1.AddTransition(transition.first.first, transition.first.second, end_state);
			}

			lnfa1.AddTransition(idx, LAMBDA, lnfa1.GetInitState());
			lnfa1.AddTransition(idx, LAMBDA, lnfa2.GetInitState());
			int lnfa1_end = lnfa1.GetAllStates().size() - 1;
			int lnfa2_end = lnfa2.GetAllStates().size() - 1;
			lnfa1.AddTransition(lnfa1_end, LAMBDA, idx + 1);
			lnfa1.AddTransition(lnfa2_end, LAMBDA, idx + 1);

			lnfa1.AddState(idx);
			lnfa1.SetInitState(idx);
			lnfa1.AddState(idx + 1);
			lnfa1.SetStateFinal(idx + 1);
			lnfa1.SetStatesCount(lnfa1.GetAllStates().size());
			idx += 2;

			lnfas_stack.push(lnfa1);
		}
	} else if (op == ".") {
		if (lnfas_stack.size() > 1) {
			LambdaNFA lnfa1 = lnfas_stack.top();
			lnfas_stack.pop();
			LambdaNFA lnfa2 = lnfas_stack.top();
			lnfas_stack.pop();

			for (int state : lnfa2.GetAllStates()) {
				lnfa1.AddState(state);
			}

			for (const auto &transition : lnfa2.GetTransitionFunction()) {
				int end_state = *transition.second.begin();
				lnfa1.AddTransition(transition.first.first, transition.first.second, end_state);
			}

			int lnfa1_end = lnfa1.GetAllStates().size() - 1;
			int lnfa2_end = lnfa2.GetAllStates().size() - 1;
			lnfa1.AddTransition(lnfa1_end, LAMBDA, lnfa2.GetInitState());
			lnfa1.SetStatesCount(lnfa1.GetAllStates().size());
			lnfa1.SetStateFinal(lnfa2_end);

			lnfas_stack.push(lnfa1);
		}
	}
}

LambdaNFA REtoLNFA(const std::string &re)
{
	std::string regex_operators = "()*|.";
	std::vector<std::string> tokens = TokenizeRE(re);
	std::vector<LambdaNFA> lnfas_vector;
	std::stack<std::string> operators_stack;
	std::stack<LambdaNFA> lnfas_stack;
	int state_idx = 0;

	for (const std::string &token : tokens) {
		if (regex_operators.find(token[0]) == std::string::npos) {
			LambdaNFA lnfa;
			lnfa.AddState(state_idx);
			lnfa.SetInitState(state_idx);

			for (char letter : token) {
				lnfa.AddState(state_idx + 1);
				lnfa.AddTransition(state_idx, letter, state_idx + 1);
				state_idx++;
			}

			lnfa.SetStateFinal(state_idx);
			lnfa.SetStatesCount(token.size());
			state_idx++;

			lnfas_vector.push_back(lnfa);
		}
	}

	std::reverse(lnfas_vector.begin(), lnfas_vector.end());
	
	for (const std::string &token : tokens) {
		if (token == "(" || token == "|" || token == "*" || token == ".") {
			operators_stack.push(token);
		} else if (token == ")") {
			while (operators_stack.empty() == false && operators_stack.top() != "(") {
				ApplyOperator(operators_stack.top(), lnfas_stack, state_idx);
				operators_stack.pop();
			}
			if (operators_stack.empty() == false) {
				operators_stack.pop();
			}
		} else {
			lnfas_stack.push(lnfas_vector.back());
			lnfas_vector.pop_back();
			while (operators_stack.empty() == false && operators_stack.top() == "*") {
				ApplyOperator(operators_stack.top(), lnfas_stack, state_idx);
				operators_stack.pop();
			}
		}
	}

	while (operators_stack.empty() == false) {
		ApplyOperator(operators_stack.top(), lnfas_stack, state_idx);
		operators_stack.pop();
	}

	LambdaNFA final_lnfa = lnfas_stack.top();
	lnfas_stack.pop();

	return final_lnfa;
}
