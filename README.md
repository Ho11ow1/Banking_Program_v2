# Banking_Program_v2

A simple yet effective banking program in ```C++```


## Features

- Account creation
- Card management
- Balance management
- Database entries


# Installation Guide

## Prerequisites
- Git installed
- G++ compiler installed
- SQLite3 installed
- Command line terminal (Command Prompt, PowerShell, or Terminal)

## Installation Steps

### 1. Clone the project
```bash
git clone https://github.com/Ho11ow1/Banking_Program_v2
```
### 2. Navigate to project directory
```bash
cd Banking_Program_v2/ConsoleApplication2
```
### 3. Compile the program
```bash
# Compile using * for all cpp files and -I for all includes, linking SQLite
g++ main.cpp src/*cpp -I./src -I./sqlite/include -L./sqlite/lib -lsqlite3 -o Bank
```
### 4. Run the program
```bash
./Bank
```

## Troubleshooting

If you encounter errors:

- Make sure you're in the correct directory
- Verify G++ is installed: `g++ --version`
- Check if all source files exist: `dir src\*.cpp`
- Ensure SQLite files are present in sqlite/include and sqlite/lib
- For Windows users, both `./Bank` and `.\Bank` will work
