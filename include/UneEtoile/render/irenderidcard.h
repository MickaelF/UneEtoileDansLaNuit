#pragma once
#include <filesystem>
#include <vector>

class AbstractTexture;

class IRenderIDCard
{
public:
    virtual ~IRenderIDCard();
    virtual void clear() = 0;

    void addTexture(std::filesystem::path path);
    void removeTexture(std::filesystem::path path);

private:
    std::vector<AbstractTexture*> m_textures;
};