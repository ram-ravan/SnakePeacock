#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scoreCard.h"
#include "startSpeed.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Task 1 - Initialise instance of scoreCard, in order to create a Score Card for the game
  ScoreCard table; 

  // Task 2 - Initialise instance of startSpeed to let the player choose an initial speed among slow, medium and fast
  startSpeed speed;


  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  float initSpeed = speed.getstartSpeedVal();
  Game game(kGridWidth, kGridHeight, initSpeed);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  // std::cout << "Score: " << game.GetScore() << "\n";
  table.WriteScoreToFile(game.GetScore());
  return 0;
}