# Shared Memory Simulation

A C program that simulates multiple processes interacting with shared memory entries. The program employs processes (peers) to perform read and write operations on shared entries, maintaining statistics such as read and write counts and time spent on each operation.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Overview

This program is designed to simulate a shared memory environment where multiple processes (peers) access shared entries. Each entry contains data and is protected by semaphores to ensure proper synchronization.

### Features

- Simulate multiple peers performing read and write operations on shared entries.
- Randomly choose whether a peer should read or write based on availability.
- Track the number of reads and writes for each entry.
- Measure and record the time spent on read and write operations.
- Use semaphores for exclusive access to entries during write operations.

## Usage

To use this program, follow these steps:

1. Clone the repository to your local machine.

```
git clone https://github.com/your-username/SharedMemory-Simulation.git
```

2. Compile the program.
```
gcc main.c -o shared_memory_simulation -lpthread
```

Execute the program with the required command-line arguments.
```
./shared_memory_simulation <peers> <entries> <read_percentage>
```
- <peers>: The number of processes (peers) to simulate.
- <entries>: The number of shared memory entries.
- <read_percentage>: The desired percentage of read operations.

## Installation
To install and run this program, you'll need:

- A C compiler (e.g., GCC)
- A POSIX-compliant operating system
- 
Follow the "Usage" instructions above to compile and execute the program.

## Contributing
Contributions are welcome! If you'd like to contribute to this project, please follow these guidelines:

1. Clone the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and commit them with descriptive commit messages.
4. Push your changes to your fork.
5. Create a pull request to the main repository's master branch.

Please ensure that your code adheres to coding standards and includes appropriate documentation.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
