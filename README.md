# CPPND: Capstone Snake Game Example

This is my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

## Tasks implemented

  1. Allowed users to enter their names and save it in a text file with their scores, so that one can get the top score
  2. Allowed the user to select the initial speed (Slow - Fast)
  3. Added a peacock as a moving obstacle to the game
  4. Displayed More than one type of food in the game
  5. Included anaconda (or a python snake) to the game and allowed the computer to control it using **A* search algorithm**

## Task 1

#### Objective

#### C++ Concepts involved

#### Steps performed to achieve the goal of the task
1. Created scoreCard.h and scoreCard.cpp with necessary data structures and its attributes, methods, constructors, destructors etc.
2. In the main(), an object of type scoreCard is created to invoke the constructor of Struct scoreCard
3. Read/Write to file operations are implemented to sort score and display top scores etc.

###### User input(s) - player name
###### Expected output/behaviour

## Task 2

#### Objective

#### C++ Concepts involved

#### Steps performed to achieve the goal of the task
1. Created startSpeed.h and startSpeed.cpp with necessary data structures and its attributes, methods, constructors, destructors etc.
2. In the main(), an object of type startSpeed is created to invoke the constructor of Struct startSpeed
1. Changed score type from int to float
2. Changed the arguments list of Game::Game(...) to set a new private attribute named initSpeed with a user selected start speed value and modified Game::Update() to  set different score increments for different modes (slow-speed)
4. Snake::Snake(...) arguments list changed, attribute Snake::speed gets initialised according to user's speed choice instead of default initialisation with 0.1f
5. Renderer::UpdateWindowTitle(..) arguments list modified and sstream library is used to display float with a score value of single precision.

###### User input(s) - User's choice of speed
###### Expected output/behaviour

## Task 3

#### Objective

#### C++ Concepts involved

#### Steps performed to achieve the goal of the task
1. New header file and source file created for peacock which is a moving obstacle in the game
2. Peacock class contains different attributes and methods to control the behaviour of peacock in the game
2. A new peacock instance is created in Game class and peacock constructor receives the grid width and grid height attributes from game class
2. Peacock moves one grid per second to one of eight directions possible in its surrounding
2. This movement of peacock is done by calling Peacock::Update(...) from game loop once in a second
3. Game::Update() is updated such that snake gets killed when its head or body touches the peacock in the game
3. Renderer::Render(...) method now has Peacock instance in its arguments list
3. Renderer::RenderPeacock(...) method receives Peacock's instance from Renderer::Render() to render it to the screen as an image using SDL_RenderCopy(...)

###### User input(s) - None
###### Expected output/behaviour

## Task 4

#### Objective

#### C++ Concepts involved

#### Steps performed to achieve the goal of the task

###### User input(s) - None
###### Expected output/behaviour

## Task 5

#### Objective

#### C++ Concepts involved

#### Steps performed to achieve the goal of the task
1. New header file and source file created for an another snake that plays as computer based on user's decision
1. New class named SnakeComp is a dervied class of Snake
1. Functions are rewritten as per the requirements of dervied class
1. User's choice of whether or not to play against another snake that is controlled by computer is received using playComputer() method in main() function
1. Create an instance of class SnakeComp in Game class and use it to set the attributes of the class and to call its methods to implement its functionality
1. A new method named Game::UpdateSnakeComp() is created to update the SnakeComp's members further calling Game::AStarSearch() (which further calls all neccessary methods to direct the SnakeComp using AStarSearch algorithm), also the name of the existing Game::Update() method is now Game::UpdateSnake()
1. Renderer::Render(...) arguments list changed accordingly to include the instance of SnakeComp
1. Renderer::RenderSnakeComp(...) method receives SnakeComp's instance from Renderer::Render() to render it to the screen

###### User input(s) - None
###### Expected output/behaviour

## Task 6

#### Objective

#### C++ Concepts involved

#### Steps performed to achieve the goal of the task

1. A function named UserEnvSetUp() is implemented in main.cpp file to let the user choose between playing against a computer or with peacock as a moving obstacle or have both in the game or to play a basic snake game
2. Changes in arguments list of Game::Game(...) and Peacock::Peacock(...) are made accordinglr to adopt this feature
3. Modifications to code in one or more methods of class Game and class Renderer are made to adopt to this game feature

User input(s) - User's choice of whether to 
1. Play against computer or
2. To play with a moving obstacle or
3. Have both in the game or
4. To play a basic snake game

###### User input(s) - User's desired choice of game environment
###### Expected output/behaviour

<!-- The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features. -->

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
