#include "appinfo.h"

#include <pttk/file/inifile.h>

#include <filesystem>
#include <optional>
AppInfoIniDesc::AppInfoIniDesc(const AppInfoIniDesc& other) noexcept
    : company(other.company),
      app(other.app),
      renderer(other.renderer)
{
}

AppInfoIniDesc::AppInfoIniDesc(AppInfoIniDesc&& other) noexcept
    : company(std::move(other.company)),
      app(std::move(other.app)),
      renderer(other.renderer)
{
    other.company.clear();
    other.app.clear();
    other.renderer = -1;
}

AppInfoIniDesc& AppInfoIniDesc::operator=(const AppInfoIniDesc& other) noexcept
{
    app = other.app;
    company = other.company;
    renderer = other.renderer;
    return *this;
}

AppInfoIniDesc& AppInfoIniDesc::operator=(AppInfoIniDesc&& other) noexcept
{
    app = std::move(other.app);
    company = std::move(other.company);
    renderer = other.renderer;
    other.company.clear();
    other.app.clear();
    other.renderer = -1;
    return *this;
}

bool AppInfoIniDesc::contains(std::string_view name) const
{
    return name == "company" || name == "app" || name == "renderer";
}

void AppInfoIniDesc::initValue(std::string_view name, std::string_view value)
{
    if (name == "company")
        company = value;
    else if (name == "app")
        app = value;
    else if (name == "renderer")
        renderer = std::stoi(std::string(value));
}

std::vector<std::pair<std::string, std::string>> AppInfoIniDesc::values() const
{
    return {{"company", company},
            {"app", app},
            {"renderer", std::to_string(renderer)}};
}

AppInfo& AppInfo::instance(const std::string& company, const std::string& app)
{
    auto path = std::filesystem::current_path().append("app.ini");
    if (!std::filesystem::exists(path))
    {
        AppInfoIniDesc desc;
        desc.app = app;
        desc.company = company;
        desc.renderer = 0;
        IniFile().save<AppInfoIniDesc>(path.string(), desc);
    }
    std::optional<AppInfoIniDesc> info =
        IniFile().readIni<AppInfoIniDesc>(path.string());
    static AppInfo instance {info->company, info->app, info->renderer};
    return instance;
}

void AppInfo::setRendererIndex(int index)
{
    if (m_rendererIndex == index) return;
    m_rendererIndex = index;
}

bool AppInfo::save()
{
    auto path = std::filesystem::current_path().append("app.ini");
    AppInfoIniDesc desc;
    desc.app = m_appName;
    desc.company = m_companyName;
    desc.renderer = m_rendererIndex;
    return IniFile().save<AppInfoIniDesc>(path.string(), desc);
}

AppInfo::AppInfo(const std::string& company, const std::string& app,
                 int renderer)
    : m_companyName(company),
      m_appName(app),
      m_rendererIndex(renderer)
{
}
