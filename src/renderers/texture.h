#pragma once
#include <filesystem>

class Texture
{
public:
    explicit Texture(int width, int height, int nbChannels);
    virtual ~Texture();
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