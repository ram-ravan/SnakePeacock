#include "game.h"
#include <iostream>
#include "SDL.h"

bool Compare(std::vector<int> a, std::vector<int> b);

Game::Game(std::size_t grid_width, std::size_t grid_height, float startSpeed, bool playAlongComputer, bool movingObstacle)
    : snake(grid_width, grid_height, startSpeed),
      peacock(grid_width, grid_height, movingObstacle),
      snakeComp(grid_width, grid_height, startSpeed, playAlongComputer),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      initSpeed(startSpeed),
      playAlongComputer(playAlongComputer),
      movingObstacle(movingObstacle) {
  PlaceFood();
  
  //Task 4
  food.w = 2;
  food.h = 2;
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    futures.emplace_back(std::async(std::launch::async, &Game::UpdateSnake, this));
    // UpdateSnake();
    renderer.Render(snake, food, peacock, snakeComp);

    if (playAlongComputer)
      // UpdateSnakeComp();
      futures.emplace_back(std::async(std::launch::async, &Game::UpdateSnakeComp, this));

    
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
      // Task 3
      if (movingObstacle)
        peacock.Update(title_timestamp, food);
    }

    for (std::future<void> &ftr : futures)
      ftr.wait();

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  ++snakeComp.placeFoodCount;
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a snake item or an obstacle before placing
    // food.
    bool place_here = false;
    if (movingObstacle)
      place_here = !snake.SnakeCell(x, y) && !peacock.PeacockCell(x, y);
    else
      place_here = !snake.SnakeCell(x, y);

    if (place_here) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::UpdateSnake() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  bool is_foodEaten = FoodCell(new_x, new_y);
  if (is_foodEaten) {
    if (initSpeed == 0.05f)
      score += 0.5;
    else if (initSpeed == 0.1f)
      score++;
    else if (initSpeed == 0.4f)
      score += 2;
    PlaceFood();
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // If the snake is in the same cells as the peacock, then the snake is killed by the peacock
 if (movingObstacle)
 {
  snake.alive = !(peacock.PeacockCell(new_x, new_y)); //Task 3

  for (auto const &item : snake.body) {
    if(peacock.PeacockCell(item.x, item.y))
      snake.alive = false;
  }
 }
}

void Game::UpdateSnakeComp() {
  if (!snakeComp.s_alive) return;

  snakeComp.Update();
  // AStarSearch();
  std::future<void> ftr = std::async(std::launch::async, &Game::AStarSearch, this);
  ftr.wait();
  int new_x = static_cast<int>(snakeComp.head.x);
  int new_y = static_cast<int>(snakeComp.head.y);

  // Check if there's food over here
  bool is_foodEaten = FoodCell(new_x, new_y);
  if (is_foodEaten) {
    if (initSpeed == 0.05f)
      score1 += 0.5;
    else if (initSpeed == 0.1f)
      score1++;
    else if (initSpeed == 0.4f)
      score1 += 2;
    PlaceFood();
    snakeComp.GrowBody();
    snakeComp.s_speed += 0.02;
  }
}

bool Game::FoodCell(int x, int y) {
  return ((food.x == x && food.y == y) || (food.x == x && food.y + 1 == y) || (food.x + 1 == x && food.y == y)
  || (food.x + 1 == x && food.y + 1 == y)); 
}

float Game::GetScore() const { return score; }
float Game::GetScore1() const { return score1; }
int Game::GetSize() const { return snake.size; }

// Task 5
// AStarSearch Algorithm

void Game::AStarSearch()
{
  h = Heuristic(snakeComp.head.x, snakeComp.head.y, food.x, food.y);
  AddToOpen(snakeComp.head.x, snakeComp.head.y, g, h);
  while (!open.empty())
  {
    current = open.back();
    open.pop_back();
    DirectSnakeComp(current[0], current[1]);
    if (FoodCell(current[0], current[1]))
      ExpandNeighbors(current);
    else
      break;
  }
  return;
}

void Game::DirectSnakeComp(int x, int y)
{
  if (x < food.x && y < food.y)
    snakeComp.s_direction = SnakeComp::Directions::kRight;
  else if (x == food.x && y > food.y)
    snakeComp.s_direction = SnakeComp::Directions::kUp;
  else if (x == food.x && y < food.y)
    snakeComp.s_direction = SnakeComp::Directions::kDown;
  else if (x > food.x && y == food.y)
    snakeComp.s_direction = SnakeComp::Directions::kLeft;
  else if (x < food.x && y == food.y)
    snakeComp.s_direction = SnakeComp::Directions::kRight;
  else if (x > food.x && y > food.y)
    snakeComp.s_direction = SnakeComp::Directions::kLeft;
}

int Game::Heuristic(int x1, int y1, int x2, int y2)
{
  return (abs(x2 - x1) + abs(y2 - y1));
}

void Game::AddToOpen(int x, int y, int g, int h)
{
  open.push_back(std::vector<int> {x, y, g, h});
  SortOpen();
}

void Game::SortOpen()
{
  std::sort(open.begin(), open.end(), Compare);
}

bool Compare(std::vector<int> a, std::vector<int> b)
{
  int f1 = a[2] + a[3]; // f1 = g1 + h1
  int f2 = b[2] + b[3]; // f2 = g2 + h2
  return f1 > f2;
}

void Game::ExpandNeighbors(std::vector<int> current)
{
  int x = current[0];
  int y = current[1];
  int g = current[2];

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++) {
      int x1 = x + delta[i][0];
      int y1 = y + delta[i][1];

      // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
      if (CheckValidCell(x1, y1)) {
        // Increment g value and add neighbor to open list.
        int g2 = g + 1;
        int h2 = Heuristic(x1, y1, food.x, food.y);
        AddToOpen(x1, y1, g2, h2);
      }
  } 
}

bool Game::CheckValidCell(int x, int y) {
  bool on_grid_x = (x >= 0 && x < snakeComp.grid_width);
  bool on_grid_y = (y >= 0 && y < snakeComp.grid_height);
  if (on_grid_x && on_grid_y && !(peacock.PeacockCell(x, y)))
    return true;
  return false;
}