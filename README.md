SLRU cache
===
This is a team project with Liza Kuzanetsova and Aslan Pliev, implementation of SLRU cache

Project structure
===
3 cache algorithms were implemented: 
- SLRU
- PSS
- LRU

Requirements
===
The following applications have to be installed:
- CMake 3.10.2 version (or higher)
- GTest
- g++

How to build
===
To compile you need to use сmake in the directory build:
```
mkdir build
cd build
сmake ..
```
To compile all:
```
make
```

Running
===
To run SLRU tests:
```
make run_cache_tests
```

To run LRU cache:
```
make run_LRUcache_tests
```

To run PSS cache:
```
make run_PSScache_cache
```

To run List:
```
make run_list_tests
```

To run HashTable:
```
make run_hash_table_tests
```