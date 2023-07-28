# My Shell

My Shell is a simple interactive shell program implemented in C. The shell allows users to enter commands and executes them by searching for the command's absolute path based on the PATH environment variable.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Limitations](#limitations)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Introduction

The shell program provides basic command execution functionality. It continuously prompts the user for commands and executes them using the `execve` system call. The `get_location` function is utilized to find the absolute path of the command based on the PATH environment variable.

## Features

- Supports basic commands execution.
- Searches for command locations based on the PATH environment variable.
- Handles invalid commands gracefully, displaying appropriate error messages.
- Provides a simple prompt `(Azubi)$ ` to indicate user input.

## Getting Started

### Prerequisites

- A C compiler, such as GCC.
- A Unix-based operating system (Linux, macOS, etc.)

### Installation

1. Clone the repository to your local machine:

`git clone https://github.com/your_username/my_shell.git`


2. Navigate to the project directory:


3. Compile the program using a C compiler, e.g., GCC:

`gcc main.c -o my_shell`


## Usage

1. Run the shell:


2. Once the shell starts, you can enter various commands just like in a regular shell.

## Limitations

- The shell does not handle advanced shell features like input/output redirection, piping, or handling signals.
- It might have limitations specific to the underlying system and the environment.

## Contributing

This project is intended as a simple educational exercise to understand the basic concepts of a shell program and the use of system calls like `execve` and environment variables like PATH. For production use or more advanced shell features, consider using existing mature shell implementations.

Contributions to the project are welcome. If you find any issues or have suggestions for improvements, feel free to create a pull request.

## License

[Insert license if applicable]. Check the LICENSE file for more details.

## Contact

For any inquiries or suggestions related to this project, please contact [Your Email Address].
