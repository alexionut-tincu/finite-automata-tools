#ifndef RE_TO_LNFA_CONVERSION_HPP
#define RE_TO_LNFA_CONVERSION_HPP

#include "lambda-nfa.hpp"
#include <stack>
#include <vector>

std::vector<std::string> TokenizeRE(const std::string &re);

void ApplyOperator(const std::string &op, std::stack<LambdaNFA> &lnfas_stack, int &idx);

LambdaNFA REtoLNFA(const std::string &re);

#endif // RE_TO_LNFA_CONVERSION_HPP