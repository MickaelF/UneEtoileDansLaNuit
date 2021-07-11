#pragma once
#include <UneEtoile/imgui/widget/appinfowidget.h>
#include <pttk/file/abstractinidefinition.h>

#include <string>

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
    int windowHeight {720};
    int windowWidth {1280};
};

class AppInfo
{
public:
    static AppInfo* instance(const std::string& company = "",
                             const std::string& app = "");

    void setRendererIndex(int index);

    const std::string& appName() const { return m_appName; }
    const std::string& companyName() const { return m_companyName; }
    int rendererIndex() const { return m_rendererIndex; }
    int windowWidth() const { return m_windowWidth; }
    int windowHeight() const { return m_windowHeight; }
    bool save();

private:
    AppInfo(const std::string& company, const std::string& app, int renderer,
            int windowWidth, int windowHeight);
    const std::string m_companyName;
    const std::string m_appName;
    int m_rendererIndex;
    int m_windowWidth;
    int m_windowHeight;

    AppInfoWidget m_widget;
    static AppInfo* m_instance;
};