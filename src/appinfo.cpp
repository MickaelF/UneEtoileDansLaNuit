#include "appinfo.h"

#include <pttk/file/inifile.h>

#include <filesystem>
#include <optional>
AppInfoIniDesc::AppInfoIniDesc(const AppInfoIniDesc& other) noexcept
    : company(other.company),
      app(other.app)
{
}

AppInfoIniDesc::AppInfoIniDesc(AppInfoIniDesc&& other) noexcept
    : company(std::move(other.company)),
      app(std::move(other.app))
{
    other.company.clear();
    other.app.clear();
}

AppInfoIniDesc& AppInfoIniDesc::operator=(const AppInfoIniDesc& other) noexcept
{
    app = other.app;
    company = other.company;
    return *this;
}

AppInfoIniDesc& AppInfoIniDesc::operator=(AppInfoIniDesc&& other) noexcept
{
    app = std::move(other.app);
    company = std::move(other.company);
    other.company.clear();
    other.app.clear();
    return *this;
}

bool AppInfoIniDesc::contains(std::string_view name) const
{
    return name == "company" || name == "app";
}

void AppInfoIniDesc::initValue(std::string_view name, std::string_view value)
{
    if (name == "company")
        company = value;
    else
        app = value;
}

std::vector<std::pair<std::string, std::string>> AppInfoIniDesc::values() const
{
    return {{"company", company}, {"app", app}};
}

AppInfo& AppInfo::instance(const std::string& company, const std::string& app)
{
    auto path = std::filesystem::current_path();
    path.append("app.ini");
    if (!std::filesystem::exists(path))
    {
        AppInfoIniDesc desc;
        desc.app = app;
        desc.company = company;
        IniFile().save<AppInfoIniDesc>(path.string(), desc);
    }
    IniFile file;

    std::optional<AppInfoIniDesc> info =
        file.readIni<AppInfoIniDesc>(path.string());
    static AppInfo instance {info->company, info->app};
    return instance;
}

AppInfo::AppInfo(const std::string& company, const std::string& app)
    : companyName(company),
      appName(app)
{
}
