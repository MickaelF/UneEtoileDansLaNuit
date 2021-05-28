#pragma once
#include <filesystem>
#include <vector>

#include <pttk/macroutils.h>
#include <UneEtoile/imgui/widget/textureexplorerwidget.h>

class AbstractTexture;

class TextureFactory
{
public:
    static TextureFactory& instance();
    AbstractTexture* generateTexture(const std::filesystem::path& path);
    void unloadTexture(AbstractTexture* tex);
    std::vector<std::pair<std::filesystem::path, AbstractTexture*>>& textures()
    {
        return m_generatedTexture;
    }

private:
    explicit TextureFactory() = default;
    DELETE_COPY_CONSTR_ASSIGN(TextureFactory)
   
    std::vector<std::pair<std::filesystem::path, AbstractTexture*>> m_generatedTexture;
    TextureExplorerWidget m_widget;
};