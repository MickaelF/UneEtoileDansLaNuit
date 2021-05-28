#pragma once
#include <filesystem>

class AbstractTexture
{
public:
    explicit AbstractTexture(int width, int height, int nbChannels);
    virtual ~AbstractTexture();
    void increaseUseNumber();
    void decreaseUseNumber();
    virtual void load(unsigned char* data) = 0;
    virtual void unload() = 0;

    const int width;
    const int height;
    const int nbChannels;

private:
    int m_numberUse {0};
};