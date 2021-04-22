#pragma once
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
};

// TODO Move this to PTTK
class AppInfo
{
public:
    static AppInfo& instance(const std::string& company = "",
                             const std::string& app = "");
    const std::string companyName;
    const std::string appName;

private:
    AppInfo(const std::string& company, const std::string& app);
};