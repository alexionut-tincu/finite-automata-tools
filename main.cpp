#include <fstream>
#include <iostream>
#include <string>

#include "re-to-lnfa-conversion.hpp"
#include "nfa-to-dfa-conversion.hpp"

int main(int argc, char *argv[])
{
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " --operation <input_file> <output_file>" << std::endl;
		return 1;
	}

	std::string operation = argv[1];
	std::string input_file = argv[2];
	std::string output_file = argv[3];

	std::ifstream input(input_file);
	if (input.is_open() == false) {
		std::cerr << "Error: could not open input file" << std::endl;
		return 1;
	}

	if (operation == "--re-to-lnfa") {
		std::string re;
		std::getline(input, re);

		LambdaNFA lnfa = REtoLNFA(re);
		std::ofstream output(output_file);
		if (output.is_open() == false) {
			std::cerr << "Error: could not open output file" << std::endl;
			return 1;
		}

		lnfa.PrintLambdaNFA(output);

		output.close();
	} else if (operation == "--lnfa-to-dfa") {
		NonDeterministicFA nfa;
		nfa.ReadNFA(input);

		DeterministicFA dfa = NFAtoDFA(nfa);
		std::ofstream output(output_file);
		if (output.is_open() == false) {
			std::cerr << "Error: could not open output file" << std::endl;
			return 1;
		}

		dfa.PrintDFA(output);

		output.close();
	} else {
		std::cerr << "Error: invalid operation" << std::endl;
		return 1;
	}

	input.close();

	return 0;
}