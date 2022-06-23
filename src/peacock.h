// Task 3

#ifndef PEACOCK_H
#define PEACOCK_H

#include <cstdlib>
#include <ctime>
#include "SDL.h"

class Peacock
{
public:

Peacock(std::size_t grid_width, std::size_t grid_height, bool movingObstacle)
: grid_width(grid_width),
  grid_height(grid_height),
  startSpeed(startSpeed),
  movingObstacle(movingObstacle) 
  {
      do
      {
        SetPosition();
      } while ((rect_peacock.x > 8 && rect_peacock.x <= 16) && (rect_peacock.y > 4 && rect_peacock.y <= 16));

      rect_peacock.h = 8;
      rect_peacock.w = 8;
  }

  Peacock(){}

    SDL_Rect rect_peacock;
    bool movingObstacle;

    bool PeacockCell(int, int);
    void Update(int seed, SDL_Rect food);

private:

    std::size_t grid_width;
    std::size_t grid_height;
    float startSpeed;

    void SetPosition();
};

#endif