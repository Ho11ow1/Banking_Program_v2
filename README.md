# Banking Program v2

A modern `C++` banking application with SQLite integration for persistent data storage.

## Features

- Secure account management
  - Account creation with validation
  - Login system
  - Account details viewing
- Card management
  - Automatic card number generation
  - PIN and CSV security
  - Card-account linking
- Balance operations
  - Deposits and withdrawals
  - Real-time balance updates
  - Synchronized account-card balance
- SQLite database integration
  - Persistent data storage
  - Transaction safety
  - Automated database setup

## Technical Stack

- C++17
- SQLite3
- Visual Studio 2022 build system
- PowerShell automation

## Prerequisites

- Visual Studio 2022 (recommended) with C++ workload
- G++ compiler (optional for alternative build method)
- Git
- PowerShell
- SQLite3 (automatically installed via setup script)

## Installation Steps

### 1. Clone the Repository
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

## 4. Build & Run

#### Method 1: Visual Studio (Recommended)
```bash
1. Open 'ConsoleApplication2.sln'
2. Build: 'Ctrl + Shift + B'
3. Run: 'Ctrl + F5'
```

#### Method 2: G++ Compiler
```bash
cd ConsoleApplication2
```
```bash
g++ main.cpp src/*.cpp src/util/*.cpp -I./src -I./sqlite/include -L./sqlite/lib -lsqlite3 -o Bank
```
```
./Bank
```

## Project Structure

```
ConsoleApplication2/
├── src/
│   ├── account.cpp/h    # Account management
│   ├── banking.cpp/h    # Main application logic
│   ├── card.cpp/h       # Card operations
│   ├── database.cpp/h   # SQLite integration
│   ├── constants.h      # Global constants
│   └── util/           # Utility functions
├── sqlite/             # SQLite dependencies
└── main.cpp           # Entry point
```

## Troubleshooting

### Common Issues
#### 1. SQLite Setup Errors:
   - Run PowerShell as Administrator
   - Enable script execution:
     ```powershell
     Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process
     ```

#### 2. Build Errors:
   - Verify Visual Studio C++ workload installation
   - Check SQLite files in sqlite/include and sqlite/lib
   - Ensure correct platform (x64) selection

#### 3. Runtime Errors:
   - Verify sqlite3.dll presence in executable directory
   - Check database file permissions

