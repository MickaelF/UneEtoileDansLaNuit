#include "textureexplorerwidget.h"

#include "imgui.h"
#include "renderers/abstractrenderer.h"
#include "renderers/opengl/opengltexture.h"
#include "renderers/texturefactory.h"
TextureExplorerWidget::TextureExplorerWidget()
    : IImGuiUserInterface("Texture Explorer")
{
}

void TextureExplorerWidget::render()
{
    static TextureFactory& texFactory = TextureFactory::instance();
    if (texFactory.textures().empty() || !visible) return;
    std::vector<std::string> names;

    for (auto& texture : texFactory.textures())
    {
        names.push_back(texture.first.filename().generic_string());
    }
    if (ImGui::Begin(name, &visible))
    {
        if (ImGui::BeginCombo("", names[m_currentIndex].c_str()))
        {
            int i = 0;
            for (auto& str : names)
            {
                const bool is_selected = (m_currentIndex == i);
                if (ImGui::Selectable(str.c_str(), is_selected))
                    m_currentIndex = i;

                // Set the initial focus when opening the combo (scrolling +
                // keyboard navigation focus)
                if (is_selected) ImGui::SetItemDefaultFocus();
                ++i;
            }
            ImGui::EndCombo();
        }
        switch (AbstractRenderer::instance()->type())
        {
            case AbstractRenderer::Type::OpenGl:
                displayOpenGlImage(
                    texFactory.textures()[m_currentIndex].second);
                break;
            default: break;
        }
        ImGui::End();
    }
}

void TextureExplorerWidget::displayOpenGlImage(Texture* tex)
{
    OpenGlTexture* currentTex = static_cast<OpenGlTexture*>(tex);
    ImGui::Image((void*)(intptr_t)currentTex->texId(),
                 ImVec2(currentTex->width, currentTex->height));
}
