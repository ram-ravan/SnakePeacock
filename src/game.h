#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "peacock.h"
#include "snakeComp.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, float startSpeed, bool playAlongComputer, bool movingObstacle);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  float GetScore() const;
  float GetScore1() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Rect food;
  Peacock peacock;
  SnakeComp snakeComp;

  float initSpeed;
  bool playAlongComputer;
  bool movingObstacle;

  std::vector<std::future<void>> futures;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  float score{0};
  // Task 5
  float score1{0};

  // Task 5
  // AStarSearch Algorithm
  std::vector<std::vector<int>> open;
  int g{0};
  int h{0};
  std::vector<int> current;
  const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  void PlaceFood();

  // Task 4
  bool FoodCell(int x, int y);

  void UpdateSnake();
  // Task 5
  void UpdateSnakeComp();

  // Task 5
  // AStarSearch Algorithm
  void AStarSearch();
  void DirectSnakeComp(int, int);
  int Heuristic(int, int, int, int);
  void AddToOpen(int, int, int, int);
  void SortOpen();
  void ExpandNeighbors(std::vector<int> current);
  bool CheckValidCell(int x, int y);
};

#endif