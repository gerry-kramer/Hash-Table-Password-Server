# Password Server with Custom Hash Table (C++)
### Created by Gerard (Gerry) Kramer for COP4530 (Data Structures II) at FSU
### Submitted December 2024
### Grade received: 100

## Overview

A password server application written in C++ using a custom-built `HashTable` class template and an adaptor class `PassServer`. The program allows loading, storing, and managing username-password pairs using encryption via the `crypt()` function from the GNU C library.

## Technologies Used
- C++ (with STL containers)
- Separate chaining hash table with `vector<list<pair<K,V>>>`
- GNU `crypt()` function (MD5-based password hashing)
- File I/O
- Makefile (Unix-style)
- Command-line interface

## Key Features

- Custom templated `HashTable<K, V>` with:
  - Insert, remove, contains, match, rehash
  - Load from file / write to file
  - Chaining-based collision resolution
- `PassServer` class (adaptor for HashTable with `string` keys/values):
  - Secure password storage (encrypted)
  - Change password with input validation
  - User addition/removal
- Menu-driven CLI interface using a provided `Menu()` function

## How to Run
```bash
make                      # builds proj5.x from Makefile
./proj5.x                 # run the main program
./proj5.x < test1         # runs taking a test file as input
```

## Complexity Analysis

As documented in assignment6_p5.txt:
- Worst-case time complexity for both rehash() and removeUser(const string &k) is O(n)

## File Overview

 - hashtable.h / hashtable.hpp: HashTable class template declaration and implementation
 - passserver.h / passserver.cpp: PassServer adaptor class
 - proj5.cpp: Main driver (uses provided Menu() interface)
 - assignment6_p5.txt: Complexity analysis
 - makefile: Build instructions

## Note on Repository

This repository was imported from one of my personal backup locations. As such, it contains no version control or commit logs. All code present in this repository is either my own original work or allowed starter code as provided by the professor.