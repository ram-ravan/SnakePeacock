// Task 3

#include "peacock.h"

void Peacock::SetPosition()
{
  srand(time(0));
  rect_peacock.x = rand() % 25;
  rect_peacock.y = rand() % 25;
}

bool Peacock::PeacockCell(int new_x, int new_y)
{
  for (size_t i = 0; i < rect_peacock.w; i++) {
    for (size_t j = 0; j < rect_peacock.h; j++) {
      if (new_x == rect_peacock.x + i && new_y == rect_peacock.y + j)
        return true;
    }
  }
  return false;
}

void Peacock::Update(int seed, SDL_Point food) // later change to SDL_Rect
{
  //Generate random numbers between -1 to +1
  srand(seed);
  int random_x = (rand()%3) - 1;
  int random_y = (rand()%3) - 1;
  int move = 0;

  if (PeacockCell(food.x, food.y))
  {
    ++move;
  }

  rect_peacock.x += random_x + move;
  rect_peacock.y += random_y + move;

  rect_peacock.x = fmod(rect_peacock.x + grid_width, grid_width);
  rect_peacock.y = fmod(rect_peacock.y + grid_height, grid_height);
}