#pragma once
#include <filesystem>

class Texture
{
public:
    explicit Texture(const std::filesystem::path& path);
    void increaseUseNumber();
    void decreaseUseNumber();

private:
    int m_width;
    int m_height;
    int m_nbChannels;
    unsigned int m_texId;
    int m_numberUse = 0;
};