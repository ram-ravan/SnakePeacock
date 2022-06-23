# CPPND: Capstone Snake Game

This is my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

This project builds upon the startup code of [Snake game](https://github.com/udacity/CppND-Capstone-Snake-Game) provided by Udacity [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

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
* SDL2_image >= 2.0
  * Install in Linux using this command [here](https://www.oreilly.com/library/view/rust-programming-by/9781788390637/ac509577-fdbc-4f2e-b876-3536985e113c.xhtml)
  * Details SDL_image 2.0 can be found [here](https://www.libsdl.org/projects/SDL_image/) and
  * To adapt SDL2_image with cmake, find details [here](https://stackoverflow.com/questions/23850472/how-to-use-sdl2-and-sdl-image-with-cmake) or [here](https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Tasks implemented

  1. Allowed users to enter their names and save it in a text file with their scores, so that one can get the top score
  2. Allowed the user to select the initial speed (Slow - Fast)
  3. Added a peacock as a moving obstacle to the game
  4. Displayed More than one type of food in the game
  5. Included another immortal snake to the game and allowed the computer to control it using **A* search algorithm**
  6. User can choose between different game modes such as 
    1. Playing against a computer or 
    2. Play with peacock as a moving obstacle or 
    3. Have both in the game or 
    4. To play a basic snake game

  New dependencies needed: SDL2_image (details in **Dependencies for Running Locally section** above)

  #### Note
   * Comments are added (with task numbers as listed above) to the code in important places so that different tasks can be identified easily
   * Apart from the major improvements and modificatins listed below for each task, there are other minor changes made to reflect the major changes that are not mentioned here
   * Scores of the snake that is controlled by computer is not stored as it is immortal and possess more power than the player

## Task 1

#### Objective - Allow users to enter their names and save it in a text file with their scores, so that one can get the top score

#### C++ Concepts involved - Basics of C++ and basics of Object Oriented Programming, File I/O

#### Steps performed to achieve the goal of the task
1. Created scoreCard.h and scoreCard.cpp with necessary data structures and its attributes, methods, constructors, destructors etc.
2. In the main(), an object of type scoreCard is created to invoke the constructor of Struct scoreCard
3. Read/Write to file operations are implemented to sort score and display top scores etc.

###### User input(s) - Player name
###### Expected output/behaviour - User gets instructions and enters the name in command line on executing ./SnakeGame in the build directory

## Task 2

#### Objective - Allow the user to select the initial speed (Slow - Fast)

#### C++ Concepts involved - Basics of C++ and basics of Object Oriented Programming

#### Steps performed to achieve the goal of the task
1. Created startSpeed.h and startSpeed.cpp with necessary data structures and its attributes, methods, constructors, destructors etc.
2. In the main(), an object of type startSpeed is created to invoke the constructor of Struct startSpeed
1. Changed score type from int to float
2. Changed the arguments list of Game::Game(...) to set a new private attribute named initSpeed with a user selected start speed value and modified Game::Update() to  set different score increments for different modes (slow-speed)
4. Snake::Snake(...) arguments list changed, attribute Snake::speed gets initialised according to user's speed choice instead of default initialisation with 0.1f
5. Renderer::UpdateWindowTitle(..) arguments list modified and sstream library is used to display float with a score value of single precision.

###### User input(s) - User's choice of speed
###### Expected output/behaviour - User gets prompted with three choices slow, normal and fast in the command line followed by entering the player name (Task 1) and choosing the game environment (Task 6)

## Task 3

#### Objective - Add a peacock as a moving obstacle to the game

#### C++ Concepts involved - Object Oriented Programming, Concurrency

#### Steps performed to achieve the goal of the task
1. New header file and source file created for peacock which is a moving obstacle in the game
2. Game::Update() (later changed to Game::UpdateSnake()) is called in the game loop using std::async(...) to make the game run faster
2. A new peacock instance is created in Game class and peacock constructor receives the grid width and grid height attributes from game class
2. Peacock moves one grid per second to one of eight directions possible in its surrounding
2. This movement of peacock is done by calling Peacock::Update(...) from game loop once in a second
3. Game::Update() is updated such that snake gets killed when its head or body touches the peacock in the game
3. Renderer::Render(...) method now has Peacock instance in its arguments list
3. Renderer::RenderPeacock(...) method receives Peacock's instance from Renderer::Render() to render it to the screen as an image using SDL_RenderCopy(...)

###### User input(s) - None
###### Expected output/behaviour - Now, a moving peacock image is rendered to the screen with the help of SDL_image library (instructions to SDL_image is in **Dependencies for Running Locally** section above)

###### Image location: Found in directory images in the same level as other project directories such as src, build etc.

## Task 4

#### Objective - Display More than one type of food in the game

#### C++ Concepts involved - Object Oriented Programming

#### Steps performed to achieve the goal of the task
1. Changed the type of Game::food from SDL_Point to SDL_Rect and change in all the source and header files accordingly to reflect the changes
2. A new method Game::FoodCell(..) was created to check if any other object is in the same grid cells where the food is
3. Created a new method Renderer::InitFoodImages() to let Renderer::foodImages attribute to hold the image paths
4. A new method Renderer::RenderFood(...) was created to render the food images to the screen

###### User input(s) - None
###### Expected output/behaviour - Many food images are listed as images using SDL_image library (instructions to SDL_image is in **Dependencies for Running Locally** section above)

###### Image location: Found in directory images in the same level as other project directories such as src, build etc.

## Task 5

#### Objective - Included another immortal snake to the game and allowed the computer to control it using **AStar search algorithm**

#### C++ Concepts involved - - Object Oriented Programming, Concurrency

#### Steps performed to achieve the goal of the task
1. New header file and source file created for an another snake that plays as computer based on user's decision
1. User's choice of whether or not to play against another snake that is controlled by computer is received using playComputer() method in main() function
1. Create an instance of class SnakeComp in Game class and use it to set the attributes of the class and to call its methods to implement its functionality
1. A new method named Game::UpdateSnakeComp() is created to update the SnakeComp's members that further calls Game::AStarSearch() 
1. Game::AStarSearch() further calls all neccessary methods to direct the SnakeComp using AStarSearch algorithm
1. The name of the existing Game::Update() method is now changed to Game::UpdateSnake()
1. Game::UpdateSnakeComp() (in the game loop) and Game::AStarSearch() are called using std::async(...) to improve the performance of the game
1. Renderer::Render(...) arguments list changed accordingly to include the instance of SnakeComp
1. Renderer::RenderSnakeComp(...) method receives SnakeComp's instance from Renderer::Render() to render it to the screen
1. In the method Renderer::UpdateWindowTitle(...), changes are made such that the scores of both player and computer can be displayed

###### User input(s) - None
###### Expected output/behaviour - User can play along an immortal snake that resists attacks from peacock and that is completely immortal. By choosing this option, user gets to play with another snake that is controlled by the computer

## Task 6

#### Objective - User choose between 
  1. Playing against a computer or 
  2. With peacock as a moving obstacle or 
  3. Have both in the game or 
  4. To play a basic snake game

#### C++ Concepts involved - Basics of C++ and basics of Object Oriented Programming 

#### Steps performed to achieve the goal of the task

1. A function named UserEnvSetUp() is implemented in main.cpp file to let the user choose between playing against a computer or with peacock as a moving obstacle or have both in the game or to play a basic snake game
2. Changes in arguments list of Game::Game(...) and Peacock::Peacock(...) are made accordinglr to adopt this feature
3. Modifications to code in one or more methods of class Game and class Renderer are made to adopt to this game feature

###### User input(s) - User's desired choice of game environments whether to 
 ###### 1. Play against computer or
 ###### 2. To play with a moving obstacle or
 ###### 3. Have both in the game or
 ###### 4. To play a basic snake game
###### Expected output/behaviour - User prompted with different options of possible game environments as listed above

## Rubric points addressed

1. The project demonstrates an understanding of C++ functions and control structures
  a. main.cpp, lines 48, 54
  b. game.cpp, lines 142, 171, 186, 230, 235, 247
  c. peacock.cpp, lines 16, 30
  d. peacock.h, line 20
  e. startSpeed.cpp, lines 9, 26
  f. scoreCard.cpp, lines 16, 28, 21, 35, 41, 56, 58, 84, 102, 112
  g. scoreComp.cpp

2. The project reads data from a file and process the data, or the program writes data to a file
  a. scoreCard.cpp, lines 9, 10, 38, 53

3. The project accepts user input and processes the input
  a. main.cpp, lines 62, 25, 26 
  a. scoreCard.cpp 18 
  a. startSpeed.cpp line 22

4. The project uses Object Oriented Programming techniques 
  a. peacock.h, lines 10 - 44
  a. snakeComp.h, lines 12 - 57
  a. peacock.cpp, all method definitions in the file and usage of member attributes in those methods
  a. snakeComp.cpp, all method definitions in the file and usage of member attributes in those methods
5. Classes use appropriate access specifiers for class members
  a. peacock.h, lines 12, 37
  a. snakeComp.h, lines 14, 50
  a. snake.h, line 37 (changed from private to protected)

6. Class constructors utilize member initialization lists
  a. peacock.h, lines 15 - 18
  a. snakeComp.h, lines 19 - 22
  a. game.cpp, lines 9 - 10, 14 - 16
7. Classes abstract implementation details from their interfaces
  a. game.cpp, new methods added across different task implementations
  a. peacock.cpp, all method definitions in the file and usage of member attributes in those methods
  a. snakeComp.cpp, all method definitions in the file and usage of member attributes in those methods
8. Classes encapsulate behavior
  a. peacock.h, contains methods and attributes related to peacock
  a. snakeComp.h, contains methods and attributes related to snakeComp
  a. game.cpp, line 161 - member attribute's state accessed via a member function
  a. startSpeed.h, lines 13, 17 - member attribute's state accessed via a member function
9. The project makes use of references in function declarations
  a. renderer.h, lines 28 - 30
10. The project uses multithreading
  a. game.cpp, lines 38, 42, 135


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
