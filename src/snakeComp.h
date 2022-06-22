// Task 5

#ifndef SNAKECOMP_H
#define SNAKECOMP_H

// #include "snake.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "SDL.h"

class SnakeComp {

public:

  enum class Directions { kUp, kDown, kLeft, kRight };

  SnakeComp(std::size_t grid_width, std::size_t grid_height, float startSpeed, bool playAlongComputer) 
  : grid_width(grid_width),
  grid_height(grid_height),
  s_speed(startSpeed),
  playAlongComputer(playAlongComputer) 
  {
    head.x = 2;
    head.y = 2;
  }

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);

  float s_speed;
  int s_size{1};
  bool s_alive{true};

  Directions s_direction = Directions::kUp;
  std::size_t grid_width;
  std::size_t grid_height;
  bool playAlongComputer;

  // Task 4
  int placeFoodCount = 0;

 struct snakeHead {
    float x, y;
 }head;

  std::vector<SDL_Point> s_body;

private:

  void UpdateHead();  
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool s_growing{false};

};

#endif