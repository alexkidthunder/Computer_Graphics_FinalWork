#ifndef FPS_H
#define FPS_H


class FPS
{
public:
    FPS();
    ~FPS();

    void CalculateFrameRate();
    float getCurrentTime();
    float getFPS();

private:
    double fps;
    float currentTime;
    float startTime;
};

#endif // FPS_H
