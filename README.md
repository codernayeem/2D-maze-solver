# 2D-maze-solver

Solve and view the solution path of a 2D Maze

## Input & Output

* __Maze Input Example__:
	
        1 1 1 1
        1 0 1 1
        1 1 1 0
        0 1 1 1
		
	* `0` => indicates __Obstacle__
	* `1` => indicates __Free Space__
	
* **Output**:
    * There can be one / multiple output maze solutions.
    * Output can be two types.
    * Normal Output will print with numbers where '2' represent solution path.
    * Fancy Output will print with some character specified in styles array.
    
* **Normal Output Example**:

        2 1 1 1 
        2 0 1 1 
        2 2 1 0 
        0 2 2 2

* **Fancy Output Example**:

        . o o o 
        . # o o 
        . . o # 
        # . . .


* **No Solution Output**:
    * `0`  => If no Solution found
    * `-1` => Start or End point is an obstacle/not in maze.


## **1. `mazeSolverOneWay.cpp`**

* Fastest. It will give a solve of the maze as soon as possible. That solve might not be the best solution.
* Can be used to check if a maze has at least one solution.

* **Input**:

        * <number of rows> <number of columns>
        * <start row> <start col> <end row> <end col>
        * <elements of the maze>

* **Input Example**:

        4 4
        1 1 4 4

        1 1 1 1
        1 0 1 1
        1 1 1 0
        0 1 1 1

* **Normal Output Example**:

        2 1 1 1 
        2 0 1 1 
        2 2 1 0 
        0 2 2 2

* **Fancy Output Example**:

        . o o o 
        . # o o 
        . . o # 
        # . . .

## **2. `mazeSolverOneBestWay.cpp`**

* It will give just one best [min steps] solution. There can be multiple best solutions. But it will just give one.
* Can be used to check one of the best [min steps] solutions of the maze.

* **Input**:

        * <number of rows> <number of columns>
        * <start row> <start col> <end row> <end col>
        * <elements of the maze>

* **Input Example**:

        4 4
        1 1 4 4

        1 1 1 0
        1 0 1 1
        0 1 1 1
        0 1 0 1

* **Output**:

        <number of min steps>
        <elements of the maze with solution>

* **Normal Output Example**:

        7

        2 2 2 0 
        1 0 2 1 
        0 1 2 2 
        0 1 0 2

* **Fancy Output Example**:

        7

        . . . # 
        o # . o 
        # o . . 
        # o # .

## **3. `mazeSolverMultiWay.cpp`**

* It will give every possible way to solve the maze.
* Can be used to see every possible solutions of the maze.

* **Input**:

        * <rows> <columns> <max solution print>
        * <start row> <start col> <end row> <end col>
        * <elements of the maze>

    * `<max solution print>` can be set to -1 to print all solution. Or, It can be a limiting value of solutions print count.

* **Input Example**:

        3 3 -1
        1 1 3 3

        1 1 1
        1 1 1
        0 0 1

* **Output**:

        <Number of Solutions>
        <solutions of maze>

* **Normal Output Example**:

        4

        2 1 1 
        2 2 2 
        0 0 2 

        2 2 2 
        2 2 2 
        0 0 2 

        2 2 1 
        1 2 2 
        0 0 2 

        2 2 2 
        1 1 2 
        0 0 2

* **Fancy Output Example**:

        4

        . o o 
        . . . 
        # # . 

        . . . 
        . . . 
        # # . 

        . . o 
        o . . 
        # # . 

        . . . 
        o o . 
        # # .

## **4. `mazeSolverMultiBestWay.cpp`**

* It will give every possible way [__minimum steps taken__] to solve the maze.
* Can be used to see every __best__ possible solutions of the maze.

* **Input**:

        * <rows> <columns> <max solution print>
        * <start row> <start col> <end row> <end col>
        * <elements of the maze>

    * `<max solution print>` can be set to -1 to print all solution. Or, It can be a limiting value of solutions print count.

* **Input Example**:

        4 4 -1
        1 1 4 3

        1 1 1 1 
        1 1 1 1
        1 1 0 1
        0 1 1 1

* **Output**:

        <Number of Solutions> <Steps taken of Each>
        <solutions of maze>

* **Normal Output Example**:

        3 6

        2 1 1 1 
        2 1 1 1 
        2 2 0 1 
        0 2 2 1 

        2 1 1 1 
        2 2 1 1 
        1 2 0 1 
        0 2 2 1 

        2 2 1 1 
        1 2 1 1 
        1 2 0 1 
        0 2 2 1

* **Fancy Output Example**:

        3 6

        . o o o 
        . o o o 
        . . # o 
        # . . o 

        . o o o 
        . . o o 
        o . # o 
        # . . o 

        . . o o 
        o . o o 
        o . # o 
        # . . o
