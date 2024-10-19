# Maze & Cave

## Installation

```git clone XXX && cd A1_Maze-1/src```

## Building

```make install``` - build program  
```make uninstall``` - remove program  
```make clean``` - clean all generated files  
```make dist``` - create archive with source code  
```make test``` - run tests  
```make gcov_report``` - generate code coverage report  

## Usage

```./build/program [-m [file]] [-c file] [-l file] [-o file] [-h num] [-w num] [-s num num] [-e num num] [-b num] [-d num] [-n num]```

### Maze Parameters

* `-m, --maze <file>`

  * Path to the maze file (optional)
  * Example: `-m maze.txt`
* `-h, --height <num>`

  * Number of rows (positive number), default is 0
  * Example: `-m -h 10`
* `-w, --width <num>`

  * Number of columns (positive number), default is 0
  * Example: `-m -w 10`
* `-s, --start <x> <y>`

  * Start position of solution (positive numbers), default is 0
  * Example: `-m -s 1 1`
* `-e, --end <x> <y>`

  * End position of solution (positive numbers), default is 0
  * Example: `-m -e 10 10`
* `-l, --learning <file>`

  * Path to the maze file for learning
  * Example: `-l maze.txt`
* `-o, --output-file <file>`

  * Path to the output file
  * Example: `-m -o output.txt`

### Cave Parameters

* `-c, --cave <file>`

  * Path to the cave file
  * Example: `-c cave.txt`
* `-b, --birth <num>`

  * Birth limit (0 <= x <= 7), default is 0
  * Example: `-c cave.txt -b 4`
* `-d, --death <num>`

  * Death limit (0 <= x <= 7), default is 0
  * Example: `-c cave.txt -d 3`
* `-n, --milliseconds <num>`

  * Render frequency in milliseconds (positive number)
  * Example: `-c cave.txt -n 500`

## Running examples

* ```./build/program -m -o output.txt -w 10 -h 10```
* ```./build/program -m maze.txt -s 1 1 -e 10 10```
* ```./build/program -l maze.txt -s 10 10```
* ```./build/program -c cave.txt -b 4 -d 3 -n 1000```
