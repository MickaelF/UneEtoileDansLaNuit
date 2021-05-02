#pragma once
#include "iimguiuserinterface.h"

class Texture;
class TextureExplorerWidget : public IImGuiUserInterface
{
public:
    TextureExplorerWidget();
    void render() override;

private:
    void displayOpenGlImage(Texture* tex);
    int m_currentIndex = 0;
};
