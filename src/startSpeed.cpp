#include <iostream>
#include <algorithm>
#include "startSpeed.h"

// This constructor implements a feature that lets the user choose the start speed while beginning the game
StartSpeed::StartSpeed()
{
    chooseSpeed:
    int count = 0;
    do
    {
        if (count > 0)
        {
            std::cout << "Please enter a valid choice. Valid choice is a number 1 or 2 or 3 from the above choices" << std::endl;
            // std::cout << "start slow or fast? \n\t  1. Slow \n\t start speed: 50 \t score increases by 0.5 \n\t 2. Normal - \n\t start speed: 100 \t score increases by 1 \n\t 3. Fast - \n\t start speed: 400 \t score increases by 2 \n\t" << std::endl;
        }
        else if (count == 0)
        {
            std::cout << "By the way, Would you like to start slow or fast? \n\t  1. Slow \n\t start speed: 50 \t score increases by 0.5 \n\t 2. Normal - \n\t start speed: 100 \t score increases by 1 \n\t 3. Fast - \n\t start speed: 400 \t score increases by 2 \n\t" << std::endl;
        }
        
        
        std::getline(std::cin, speed);
        count++;
    } while (speed != "1" && speed != "2" && speed != "3");
    
        switch (std::stoi(speed))
        {
            case 1: startSpeedVal = 0.05f;
            break;

            case 2: startSpeedVal = 0.1f;
            break;

            case 3: startSpeedVal = 0.4f;
            break;

            default: goto chooseSpeed;
        }
}