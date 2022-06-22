#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "peacock.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, float startSpeed);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  float GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  Peacock peacock;

  float initSpeed;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  float score{0};

  void PlaceFood();
  void Update();
};

#endif