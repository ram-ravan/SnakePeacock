#ifndef STARTSPEED_H
#define STARTSPEED_H

struct startSpeed
{
    private:

    char speed;
    float startSpeedVal;

    public:
    startSpeed();
    float getstartSpeedVal() const
    {
        return startSpeedVal;
    }
    char getSpeed() const
    {
        return speed;
    }
};
#endif