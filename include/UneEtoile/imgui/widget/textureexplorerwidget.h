#pragma once
#include <UneEtoile/imgui/iimguiuserinterface.h>

class AbstractTexture;
class TextureExplorerWidget : public IImGuiUserInterface
{
public:
    TextureExplorerWidget();
    void render() override;

private:
    void displayOpenGLImage(AbstractTexture* tex);
    int m_currentIndex = 0;
};
