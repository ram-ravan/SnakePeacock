// Task 5

#include "snakeComp.h"

void SnakeComp::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head.x),
      static_cast<int>(
          head.y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head.x),
      static_cast<int>(head.y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void SnakeComp::UpdateHead() {
  switch (s_direction) {
    case Directions::kUp:
      head.y -= s_speed;
      break;

    case Directions::kDown:
      head.y += s_speed;
      break;

    case Directions::kLeft:
      head.x -= s_speed;
      break;

    case Directions::kRight:
      head.x += s_speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head.x = fmod(head.x + grid_width, grid_width);
  head.y = fmod(head.y + grid_height, grid_height);
}

void SnakeComp::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  s_body.push_back(prev_head_cell);

  if (!s_growing) {
    // Remove the tail from the vector.
    s_body.erase(s_body.begin());
  } else {
    s_growing = false;
    s_size++;
  }
  //This snake is immortal, hence no implementations to kill this one like the one found in Snake::UpdateBody(...)

}

void SnakeComp::GrowBody() { s_growing = true; }

// Changed to an efficient method to check if cell is occupied by snake.
bool SnakeComp::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head.x) && y == static_cast<int>(head.y)) {
    return true;
  }
  if (s_size > 1) {  
    bool snakeCell_x = (x >= s_body[0].x && x <= s_body[s_body.size()-1].x);
    bool snakeCell_y = (y >= s_body[0].y && y <= s_body[s_body.size()-1].y);
    if (snakeCell_x && snakeCell_y)
      return true;
  }
  return false;
  return false;
}