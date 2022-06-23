#include <iostream>
#include <algorithm>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scoreCard.h"
#include "startSpeed.h"

int UserEnvSetUp();

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Task 1 - Initialise instance of scoreCard, in order to create a Score Card for the game
  ScoreCard table;

  // Task 6 - Let the user choose between playing against a computer or with peacock as a moving obstacle or have both in the game or to play a basic snake game
  int userEnvSetUp = UserEnvSetUp();

  bool playAlongComputer = ((userEnvSetUp == 1 || userEnvSetUp == 3) && userEnvSetUp != 4);
  bool movingObstacle = ((userEnvSetUp == 2 || userEnvSetUp == 3) && userEnvSetUp != 4);

  // Task 2 - Initialise instance of startSpeed to let the player choose an initial speed among slow, medium and fast
  startSpeed speed;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  float initSpeed = speed.getstartSpeedVal();
  Game game(kGridWidth, kGridHeight, initSpeed, playAlongComputer, movingObstacle);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  // std::cout << "Score: " << game.GetScore() << "\n";
  
  table.WriteScoreToFile(game.GetScore());
    if (playAlongComputer)
    table.PrintComputerScore(game.GetScore1());
  
  return 0;
}

// Task 6
int UserEnvSetUp()
  {
    std::cout << "How would you like to challenge yourself? Play against computer or have a moving obstacle?" << std::endl;
    int user_input;
    bool bool_output;
    int count = 0;
    do
    {

      if (count > 0)
        std::cout << "Please reply a valid inputs!! type number 1, 2, 3 or 4 based on below?" << std::endl;
      std::cout << "Choose \t 1. Play against Computer or \nchoose \t 2. Have a peacock as a moving obstacle in the game? or \nchoose \t 3. Have both in the game or \nchoose \t 4. Basic snake game" << std::endl;
      // getline(std::cin, user_input);
      count++;
    } while (!(std::cin >> user_input) || user_input < 1 || user_input > 4);
    return static_cast<int>(user_input);
  }