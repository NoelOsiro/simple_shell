# UNIX Command Line Interpreter

This is a custom UNIX command line interpreter built from scratch. It provides a shell-like environment where users can interact with the system through command line inputs.

## Features

- Command execution: Run various UNIX commands and programs.
- Shell built-in commands: Implement built-in commands such as `cd`, `echo`, `pwd`, etc.
- Input/Output Redirection: Support input/output redirection using `<`, `>`, `>>`.
- Pipelines: Allow command chaining using pipes `|` to redirect output from one command to another.
- Environment Variables: Implement support for environment variables.
- Command History: Store and retrieve previously executed commands.
- Customizable Prompt: Allow customization of the shell prompt.

## Getting Started

To use the UNIX command line interpreter, follow these steps:

1. Clone this repository: `git clone https://github.com/your-username/unix-command-line-interpreter.git`
2. Build the interpreter: `make`
3. Run the interpreter: `./interpreter`

## Usage

Once the interpreter is running, you can enter various UNIX commands and interact with the system. Some example commands you can try are:

$ ls -l
$ cd path/to/directory
$ echo "Hello, World!"
$ pwd
$ grep "keyword" file.txt
$ command1 | command2
$ command < input.txt > output.txt

Refer to the documentation or source code for the complete list of supported commands and features.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
