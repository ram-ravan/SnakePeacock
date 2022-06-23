#ifndef STARTSPEED_H
#define STARTSPEED_H

struct StartSpeed
{
    private:

    std::string speed;
    float startSpeedVal;

    public:
    StartSpeed();
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