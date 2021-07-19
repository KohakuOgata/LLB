#pragma once

#include <list>

class Fps {

public:
    Fps();
    void Wait();
    void Draw() const;

private:
    std::list<int> flameTimes;
    float    fps;
    unsigned counter;

    void        UpdateAverage();
    void        Regist();
    unsigned    GetWaitTime() const;

};