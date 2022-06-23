#include "scoreCard.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>

std::ofstream writeFile("./scoresInFloat.txt", std::ofstream::app);
std::ifstream ReadFile;
std::string line;

ScoreCard::ScoreCard()
    {   
        std::cout << "Enter player name: ";
        do
        {
            std::getline(std::cin, playerName);
            if (playerName.empty())
            {
                std::cout << "Please enter a name to play!" << std::endl;
            }
            
        } while (playerName.empty());
        std::cout << "Great " << playerName << "! Time to see how good are you in this classic game, but we have a small message before the game starts!!\n" << std::endl;
        std::cout << "Press Enter key to read an important messages about the game" << std::endl;
        char enter;
        do {enter = getchar();} while(enter != '\n');
        std::cout << "\t\t--------------------------------------------------------------------------------------------------\t\t" << std::endl;
        std::cout << "Peacocks really like to eat snakes! Beware of peacock in the game!" << std::endl; // Task 3 
        do {enter = getchar();} while(enter != '\n');
        std::cout << "Your score is stored only if you play until the game ends when snake dies. If you quit the game in the middle, your score is not stored..!" << std::endl;
        std::cout << "\t\t--------------------------------------------------------------------------------------------------\t\t" << std::endl;
        std::cout << "Press Enter key to start playing!" << std::endl;
        do {enter = getchar();} while(enter != '\n');
    }

void ScoreCard::WriteScoreToFile(float score)
{
    ScoreCard::score = score;
    if (writeFile.is_open())
    {
        writeFile << playerName  + ":" + std::to_string(score) + "\n";
        writeFile.close();
    }
    else
    {
        std::cout << "Problem with open file!";
    }
    ReadScoreFromFile();
}

void ScoreCard::ReadScoreFromFile()
{   
    ReadFile.open("./scoresInFloat.txt");
    if(ReadFile.is_open())
    {
        while (std::getline(ReadFile, line))
        {
            std::size_t position = line.find(":");
            float scoreFromFile = std::stof(line.substr(position + 1 , line.size()));
            // std::cout << "ScoreFromFile: " << scoreFromFile << std::endl;
            std::string playerFromFile = line.substr(0, position);
            scoresTable.emplace_back(playerFromFile, scoreFromFile); //store the player names and scores in scoresTable to sort scores in descending order and to find max score.
        }
        SortScores();
    }
}

void ScoreCard::SortScores()
{
    std::sort(scoresTable.begin(), scoresTable.end(), [](std::pair <std::string, float> a, std::pair <std::string, float> b) { return a.second > b.second; });
}

void ScoreCard::MaxScore()
{
    maxScoredPlayer = scoresTable.front();
}

ScoreCard::~ScoreCard()
{
    MaxScore();
    int loop = 0;
    if (score > getmaxScoredPlayer()->second)
    {
        std::cout << "\t\t Congratulations!! You have set a new highscore beating " << getmaxScoredPlayer()->first << "." << std::endl;
    }
    else if (score == getmaxScoredPlayer()->second)
    {
        std::cout << "\t\t Congratulations!! You have set a new highscore sharing top spot with " << getmaxScoredPlayer()->first << "." << std::endl;
    }
    
    else if (score >= 10.0 && score < getmaxScoredPlayer()->second)
    {
        std::cout << "\t\t Good work, you are a great player!!! Enjoy playing and improve further!! And all the best for setting a new high score!" << std::endl;
    }
    std::cout << "\n\t\t->->->->->->->->->->->->->->  Your score is " << score << " " << playerName << "!  <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<\t\t\n" << std::endl;
    std::cout << "\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \t\t" << std::endl;
    std::cout << "\t\t#############################  Game stats  ##################################\t\t\n" << std::endl;
    std::cout << "\t\t++++++++++++++++++++++++++++  Total number of games played: " << scoresTable.size() << "  ++++++++++++++++++++++++++++++++\t\t" << std::endl;
    std::cout << "\t\t\n\t\t->->->->->->->->->->->->->->  Highest score is " << getmaxScoredPlayer()->second << " by " << getmaxScoredPlayer()->first << "  <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<\t\t" << std::endl;
    if (scoresTable.size() < 10)
    {
        std::cout << "\n\t\t+++++++++++++++++++Top " << scoresTable.size() << " scores+++++++++++++++++++++\t\t" << std::endl;
        loop = scoresTable.size();
    }
    else
    {
        std::cout << "\n\t\t+++++++++++++++++++Top 10 scores+++++++++++++++++++++\t\t" << std::endl;
        loop = 10;
    }
    for (int i = 0; i < loop; i++)
    {   
        std::cout << "\t\t(" << i+1 << ") " << scoresTable[i].first << ": " << scoresTable[i].second << std::endl;
    }
    std::cout << "\t\t--------------------------------------------------------------------------------------------------\t\t" << std::endl;
    std::cout << "\t\t--------------------------------------------------------------------------------------------------\t\t" << std::endl;
    std::cout << "\t\t--------------------------------------------------------------------------------------------------\t\t" << std::endl;
    
}

void ScoreCard::PrintComputerScore(float score)
{
    std::cout << "\n\t\t->->->->->->->->->->->->->->  Computer's score is " << score << " " << "!  <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<\t\t\n" << std::endl;
}