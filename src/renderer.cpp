#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);

  // Task 3
  SDL_FreeSurface(surface_peacock);
  SDL_DestroyTexture(texture_peacock);

  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Rect const &food, Peacock const peacock, SnakeComp const snakeComp) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  RenderFood(food, snakeComp.placeFoodCount);
  // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  // block.x = food.x * block.w;
  // block.y = food.y * block.h;
  // SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xAA, 0x00, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

if (snakeComp.playAlongComputer)
  RenderSnakeComp(snakeComp);

  //Task 3
  // std::future<void> ftr = std::async(std::launch::async, &Renderer::RenderPeacock, this, peacock);
  // std::thread t(&Renderer::RenderPeacock, this, peacock);
if (peacock.movingObstacle)
    RenderPeacock(peacock);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
    // t.join();
    // ftr.wait();
}

void Renderer::UpdateWindowTitle(float score, int fps) {
  // std::string title;
  // Task 2
  std::stringstream stream;
  stream << std::fixed << std::setprecision(1) << score;
  std::string preciseScore = stream.str();
  std::string title{"Snake Score: " + preciseScore + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderPeacock(Peacock const &peacock) {
  SDL_Rect render_peacock;
  render_peacock.w = screen_width / grid_width;
  render_peacock.h = screen_height / grid_height;
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xFF, 0xFF);
  render_peacock.x = peacock.rect_peacock.x * render_peacock.w;
  render_peacock.y = peacock.rect_peacock.y * render_peacock.h;
  render_peacock.w = peacock.rect_peacock.w * render_peacock.w;
  render_peacock.h = peacock.rect_peacock.h * render_peacock.h;
  // SDL_RenderFillRect(sdl_renderer, &render_peacock);

  // For loading JPG images
  IMG_Init(IMG_INIT_PNG);

  // SDL_Surface is to handover the image using software rendering to the hardware rendering
  surface_peacock = IMG_Load(PATH);

  //Filling texture with the image using a surface
  texture_peacock = SDL_CreateTextureFromSurface(sdl_renderer, surface_peacock);

  //Copying the texture on to the window using renderer and rectangle
  SDL_RenderCopy(sdl_renderer, texture_peacock, NULL, &render_peacock);
}

void Renderer::RenderSnakeComp(SnakeComp const &snakeComp) {
  // Render snakeComp's body
  SDL_Rect renderSnakeComp;
  renderSnakeComp.w = screen_width / grid_width;
  renderSnakeComp.h = screen_height / grid_height;
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xAA, 0xAA, 0xFF);
  for (SDL_Point const &point : snakeComp.s_body) {
    renderSnakeComp.x = point.x * renderSnakeComp.w;
    renderSnakeComp.y = point.y * renderSnakeComp.h;
    SDL_RenderFillRect(sdl_renderer, &renderSnakeComp);
  }

  // Render snake's head
  renderSnakeComp.x = static_cast<int>(snakeComp.head.x) * renderSnakeComp.w;
  renderSnakeComp.y = static_cast<int>(snakeComp.head.y) * renderSnakeComp.h;
  if (snakeComp.s_alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0x7A, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &renderSnakeComp);
}

void Renderer::RenderFood(SDL_Rect const &food, int updateFood) {
    // Render food
  SDL_Rect sdl_food;
  sdl_food.w = screen_width / grid_width;
  sdl_food.h = screen_height / grid_height;

//Task 4
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); 
  sdl_food.x = food.x * sdl_food.w; 
  sdl_food.y = food.y * sdl_food.h;
  sdl_food.w = food.w * sdl_food.w;
  sdl_food.h = food.h * sdl_food.h;
  // SDL_RenderFillRect(sdl_renderer, &sdl_food);
  InitFoodImages();
  IMG_Init(IMG_INIT_PNG);
    imageIndex =  ((int) updateFood) % foodImages.size();
  
  // surface_food = IMG_Load(foodImages[7]);
  surface_food = IMG_Load(foodImages[imageIndex]);
  texture_food = SDL_CreateTextureFromSurface(sdl_renderer, surface_food);
  SDL_RenderCopy(sdl_renderer, texture_food, NULL, &sdl_food);
}

void Renderer::InitFoodImages() {
  foodImages.emplace_back("../images/insect.png");     // 01
  foodImages.emplace_back("../images/spider.png");     // 02
  foodImages.emplace_back("../images/lizard.png");     // 03
  foodImages.emplace_back("../images/frog.png");       // 04
  foodImages.emplace_back("../images/rat.png");        // 05
  foodImages.emplace_back("../images/fish.png");       // 06
  foodImages.emplace_back("../images/apple.png");      // 07
  foodImages.emplace_back("../images/strawberry.png"); // 08
  foodImages.emplace_back("../images/watermelon.png"); // 09
  foodImages.emplace_back("../images/bird.png");       // 10
  foodImages.emplace_back("../images/rooster.png");    // 11       
  foodImages.emplace_back("../images/duck.png");       // 12
  foodImages.emplace_back("../images/hare.png");       // 13 
  foodImages.emplace_back("../images/turkey.png");     // 14         
  // foodImages.emplace_back("../images/cat.png");// (14)
  foodImages.emplace_back("../images/cat2.png");       // 15
  foodImages.emplace_back("../images/penguin.png");    // 16
}