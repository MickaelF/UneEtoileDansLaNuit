#pragma once
#include <filesystem>
#include <vector>

#include <UneEtoile/imgui/widget/textureexplorerwidget.h>

class Texture;

class TextureFactory
{
public:
    static TextureFactory& instance();
    Texture* generateTexture(const std::filesystem::path& path);
    void unloadTexture(Texture* tex);
    std::vector<std::pair<std::filesystem::path, Texture*>>& textures()
    {
        return m_generatedTexture;
    }

private:
    explicit TextureFactory() = default;
    TextureFactory(const TextureFactory&) = delete;
    TextureFactory(TextureFactory&&) = delete;
    TextureFactory& operator=(const TextureFactory&) = delete;
    TextureFactory& operator=(TextureFactory&&) = delete;

    std::vector<std::pair<std::filesystem::path, Texture*>> m_generatedTexture;
    TextureExplorerWidget m_widget;
};