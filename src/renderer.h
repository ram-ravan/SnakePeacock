#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <thread>
#include <future>
#include "SDL.h"
#include "snake.h"
#include "peacock.h"
// Task 3
#include "SDL_image.h"
// Task 5
#include "snakeComp.h"

#define PATH "../images/peacock_withoutBG_l.png"   // Licensed images from https://www.shutterstock.com | User ID: 333340777 | 500 × 441 pixels 2 × 2 in·300 DPI

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Rect const &food, Peacock const peacock, SnakeComp const snakeComp);
  void UpdateWindowTitle(float score, float score1, int fps, bool playAlongComputer);
  void RenderPeacock(Peacock const &peacock);
  void RenderSnakeComp(SnakeComp const &SnakeComp);
  void RenderFood(SDL_Rect const &food, int);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  // Task 3
  SDL_Texture* texture_peacock = NULL; // used for hardware rendering using GPU
  SDL_Surface* surface_peacock;

  // Task 4
  SDL_Texture* texture_food = NULL;
  SDL_Surface* surface_food;

  // Task 4
  int imageIndex = 0;
  std::vector<char const*> foodImages;
  

  // Task 4
  void InitFoodImages();
};

#endif