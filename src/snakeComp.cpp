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

  // Check if the snake has died.
//   for (auto const &item : s_body) {
//     if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
//       s_alive = false;
//     }
//   }
}

void SnakeComp::GrowBody() { s_growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool SnakeComp::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head.x) && y == static_cast<int>(head.y)) {
    return true;
  }
  for (auto const &item : s_body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}