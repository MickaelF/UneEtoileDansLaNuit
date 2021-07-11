#include <UneEtoile/appinfo.h>
#include <pttk/file/inifile.h>

#include <filesystem>
#include <optional>

AppInfo* AppInfo::m_instance {nullptr};

AppInfoIniDesc::AppInfoIniDesc(const AppInfoIniDesc& other) noexcept
    : company(other.company),
      app(other.app),
      renderer(other.renderer),
      windowWidth(other.windowWidth),
      windowHeight(other.windowHeight)
{
}

AppInfoIniDesc::AppInfoIniDesc(AppInfoIniDesc&& other) noexcept
    : company(std::move(other.company)),
      app(std::move(other.app)),
      renderer(other.renderer),
      windowWidth(other.windowWidth),
      windowHeight(other.windowHeight)
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
    windowWidth = other.windowWidth;
    windowHeight = other.windowHeight;
    return *this;
}

AppInfoIniDesc& AppInfoIniDesc::operator=(AppInfoIniDesc&& other) noexcept
{
    app = std::move(other.app);
    company = std::move(other.company);
    renderer = other.renderer;
    windowWidth = other.windowWidth;
    windowHeight = other.windowHeight;
    other.company.clear();
    other.app.clear();
    other.renderer = -1;
    return *this;
}

bool AppInfoIniDesc::contains(std::string_view name) const
{
    return name == "company" || name == "app" || name == "renderer" ||
           name == "windowWidth" || name == "windowHeight";
}

void AppInfoIniDesc::initValue(std::string_view name, std::string_view value)
{
    if (name == "company")
        company = value;
    else if (name == "app")
        app = value;
    else if (name == "renderer")
        renderer = std::stoi(std::string(value));
    else if (name == "windowWidth")
        windowWidth = std::stoi(std::string(value));
    else if (name == "windowHeight")
        windowHeight = std::stoi(std::string(value));
}

std::vector<std::pair<std::string, std::string>> AppInfoIniDesc::values() const
{
    return {{"company", company},
            {"app", app},
            {"renderer", std::to_string(renderer)},
            {"windowWidth", std::to_string(windowWidth)},
            {"windowHeight", std::to_string(windowHeight)}};
}

AppInfo* AppInfo::instance(const std::string& company, const std::string& app)
{
    if (m_instance) return m_instance;

    auto path = std::filesystem::current_path().concat("/app.ini");
    std::optional<AppInfoIniDesc> info;
    if (!std::filesystem::exists(path))
    {
        info = AppInfoIniDesc {};
        info->app = app;
        info->company = company;
        IniFile().save<AppInfoIniDesc>(path.string(), *info);
    }
    else
    {
        info = IniFile().readIni<AppInfoIniDesc>(path.string());
    }
    m_instance = new AppInfo {info->company, info->app, info->renderer,
                              info->windowWidth, info->windowHeight};
    return m_instance;
}

void AppInfo::setRendererIndex(int index)
{
    if (m_rendererIndex == index) return;
    m_rendererIndex = index;
}

bool AppInfo::save()
{
    AppInfoIniDesc desc;
    desc.app = m_appName;
    desc.company = m_companyName;
    desc.renderer = m_rendererIndex;
    desc.windowHeight = m_windowHeight;
    desc.windowWidth = m_windowWidth;
    return IniFile().save<AppInfoIniDesc>(
        std::filesystem::current_path().concat("app.ini").string(), desc);
}

AppInfo::AppInfo(const std::string& company, const std::string& app,
                 int renderer, int windowWidth, int windowHeight)
    : m_companyName(company),
      m_appName(app),
      m_rendererIndex(renderer),
      m_windowWidth(windowWidth),
      m_windowHeight(windowHeight)
{
}
