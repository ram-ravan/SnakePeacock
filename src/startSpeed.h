#ifndef STARTSPEED_H
#define STARTSPEED_H

struct startSpeed
{
    private:

    std::string speed;
    float startSpeedVal;

    public:
    startSpeed();
    float getstartSpeedVal() const
    {
        return startSpeedVal;
    }
    std::string getSpeed() const
    {
        return speed;
    }
};
#endif