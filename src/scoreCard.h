#ifndef SCORECARD_H
#define SCORECARD_H

#include <vector>
#include <string>
#include <utility>

struct ScoreCard {

    private:

        std::vector<std::pair<std::string, float>> scoresTable;
        std::string playerName;
        float score;
        float score1;
        std::pair<std::string, float> maxScoredPlayer;

        void ReadScoreFromFile();
        void SortScores();
        void MaxScore();

    public:

        auto getScoresTable() const
        {
            return &scoresTable;
        }

        auto getmaxScoredPlayer() const
        {
            return &maxScoredPlayer;
        }

        ScoreCard();
        ~ScoreCard();
        void WriteScoreToFile(float score);
        void PrintComputerScore(float score);

};

#endif