# Banking_Program_v2

A simple yet effective banking program in ```C++```


## Features

- Account creation
- Card management
- Balance management
- Database entries


# Installation Guide

## Prerequisites
- Visual Studio 2022 (recommended)
- G++ compiler installed (optional)
- Git installed
- SQLite3 installed
- PowerShell

## Installation Steps

### 1. Clone the project
```bash
git clone https://github.com/Ho11ow1/Banking_Program_v2
```

### 2. Navigate to project directory
```bash
cd Banking_Program_v2
```

### 3. Run the Setup Script
```powershell
# Open PowerShell as Administrator and run:
.\setup-sqlite.ps1
```

### Main Method: Using Visual Studio (Recommended)

1. Open `ConsoleApplication2.sln` in Visual Studio
2. Select your preferred build configuration (Debug/Release) and platform (x64/x86)
3. Build the solution (Ctrl + Shift + B)
4. Run the program (Ctrl + F5)

### Alternative Method: Using g++ Compiler

1. Navigate to the project directory:
```bash
cd Banking_Program_v2/ConsoleApplication2
```

2. Compile the program:
```bash
g++ main.cpp src/*.cpp src/util/*.cpp -I./src -I./sqlite/include -L./sqlite/lib -lsqlite3 -o Bank
```

3. Run the program:
```bash
./Bank
```

## Troubleshooting

If you encounter errors:

- Make sure you're in the correct directory
- Verify Visual Studio 2022 has `C++` installed (only if using Visual Studio method)
- Verify G++ compiler is properly installed (only if using alternative method)
- Ensure SQLite files are present in sqlite/include and sqlite/lib
- For PowerShell script execution issues:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```
