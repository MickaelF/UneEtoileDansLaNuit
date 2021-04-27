#pragma once
#include <pttk/file/abstractinidefinition.h>

#include <string>

#include "imgui/appinfowidget.h"

class AppInfoIniDesc : public AbstractIniDescription
{
public:
    AppInfoIniDesc() = default;
    ~AppInfoIniDesc() = default;
    AppInfoIniDesc(const AppInfoIniDesc& other) noexcept;
    AppInfoIniDesc(AppInfoIniDesc&& other) noexcept;

    AppInfoIniDesc& operator=(const AppInfoIniDesc& other) noexcept;
    AppInfoIniDesc& operator=(AppInfoIniDesc&& other) noexcept;

    bool contains(std::string_view name) const override;
    void initValue(std::string_view name, std::string_view value) override;

    std::vector<std::pair<std::string, std::string>> values() const override;
    std::string company;
    std::string app;
    int renderer {0};
};

class AppInfo
{
public:
    static AppInfo& instance(const std::string& company = "",
                             const std::string& app = "");

    void setRendererIndex(int index);

    const std::string& appName() const { return m_appName; }
    const std::string& companyName() const { return m_companyName; }
    int rendererIndex() const { return m_rendererIndex; }
    bool save();

private:
    AppInfo(const std::string& company, const std::string& app, int renderer);
    std::string m_companyName;
    std::string m_appName;
    int m_rendererIndex;
    AppInfoWidget m_widget;
};