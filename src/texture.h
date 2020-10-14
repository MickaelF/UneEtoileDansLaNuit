#pragma once 
#include <filesystem>

class Texture
{
public: 
    explicit Texture(const std::filesystem::path& path);


private:
    int m_width; 
    int m_height; 
    int m_nbChannels; 
    unsigned int m_texId; 
};