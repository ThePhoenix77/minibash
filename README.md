# Minibash

Welcome to **Minibash**, a custom shell implementation designed to mimic the behavior of the Bash shell. This project serves as a practical exercise in understanding shell mechanics, process management, and command execution in Unix-like operating systems.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
- [Installation](#installation)
- [Usage](#usage)
- [Commands Implemented](#commands-implemented)
- [Environment Variables](#environment-variables)
- [Error Handling](#error-handling)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Command Execution**: Execute a variety of shell commands, including built-in commands and external binaries.
- **Piping and Redirection**: Support for piping (`|`) and redirection (`>`, `<`) to manipulate input and output streams.
- **Built-in Commands**: Includes essential commands such as `cd`, `echo`, `exit`, `env`, and `export`, with full functionality.
- **Signal Handling**: Proper handling of Unix signals (like `SIGINT` and `SIGQUIT`) for a responsive user experience.
- **Environment Management**: Maintain and manipulate environment variables seamlessly.
- **Customizable**: Easily extendable to add new features and commands.

## Getting Started

To get started with Minibash, clone the repository and compile the source code.

### Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd minishell


2. Compile the source code:
   ```bash
   make


3. Run the shell:
   ```bash
   ./minishell

## Usage

Once you launch Minibash, you will see a prompt where you can enter your commands. Simply type your command and press Enter.
The shell will execute the command and display the output.

  *  Example Commands:
   ```bash
    echo "Hello, World!"       # Outputs: Hello, World!
    cd /path/to/directory      # Change current directory
    ls -la                      # List files in the current directory
    export MY_VAR="Value"      # Set an environment variable
    env                         # Display environment variables
  ```

## Commands Implemented

  Minibash supports a variety of built-in commands:
   *  cd [path]: Change the current directory.
     
   *  echo [string]: Print the specified string to the standard output.
     
   *  exit [status]: Exit the shell with the specified status.
     
   *  env: Display the current environment variables.
     
   *  export [variable=value]: Set or update environment variables.
     
   *  unset [variable]: Remove environment variables.
     

## Environment Variables

  Minibash allows you to manage environment variables using the export and unset commands. You can check 
  the current environment variables using the env command.

  *  Example Usage:
   ```bash
    export MY_VAR="Hello"      # Set environment variable
    echo $MY_VAR               # Outputs: Hello
    unset MY_VAR               # Remove environment variable
  ```

## Error Handling

  Minibash provides comprehensive error handling for various scenarios, including:

  *  Invalid commands
  
  *  Incorrect usage of built-in commands
    
  *  Errors during file operations (e.g., redirection failures)
    
  *  Error messages are displayed to the user to aid in debugging.

## Contributing

  Contributions are welcome! If you have suggestions for improvements or new features,
  please fork the repository and submit a pull request.

## License

  This project is licensed under the MIT License - see the LICENSE file for details.




























