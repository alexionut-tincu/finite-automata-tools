# Finite Automata Tools

This project provides a set of tools for working with finite automata, including deterministic finite automata (DFA), non-deterministic finite automata (NFA), and lambda-NFAs. It also includes functionality for converting regular expressions to lambda-NFAs and NFAs to DFAs.

## Building the Project

This project uses CMake for building. To build the project, navigate to the project directory in your terminal and run the following commands:

```sh
mkdir build
cd build
cmake ..
make
```

This will create an executable in the `build` directory.

## Running the Program

To run the program, navigate to the `build` directory and execute the following command:

```sh
./finite-automata-tools
```

## Command-Line Arguments

The program accepts command-line arguments to specify the operation and the input. The general format is:

```sh
./finite-automata-tools [operation] [input-file] [output-file]
```

- `[operation]`: Specifies the operation to perform. This can be one of the following:
  - `--re-to-lnfa`: Convert a regular expression to a lambda-NFA.
  - `--nfa-to-dfa`: Convert an NFA to a DFA.
- `[input-file]`: Specifies the input file containing the data for the operation.
- `[output-file]`: Specifies the output file where the result of the operation will be written.

For example, to convert a regular expression to a lambda-NFA, you would run:

```sh
./finite-automata-tools --re-to-lnfa input.txt output.txt
```

This will output a representation of the lambda-NFA that corresponds to the regular expression `(a|b)*abb`.

## Licensing

The Finite Automata Tools project is licensed under the GNU General Public License v3.0. By contributing to the project, you agree that your contributions will be licensed under the same terms. For more details, please see the [`LICENSE.md`](command:_github.copilot.openRelativePath?%5B%22LICENSE.md%22%5D "LICENSE.md") file in the project repository.