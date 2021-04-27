#pragma once
#include "iimguiuserinterface.h"

class AppInfoWidget : public IImGuiUserInterface
{
public:
    AppInfoWidget();
    void render() override;

private:
    bool hasChanges() const;
    bool needRestart() const;
    void save();
    int m_currentRenderer {-1};
    bool m_modifying = false;
};