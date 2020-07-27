#pragma once
#include <string_view>
#include <string>

#include "abstractinidefinition.h"

class WindowIniFile : public AbstractIniDescription
{
public:
    WindowIniFile() = default;
    ~WindowIniFile() = default;
    WindowIniFile(const WindowIniFile& other) noexcept;
    WindowIniFile(WindowIniFile&& other) noexcept;

    WindowIniFile& operator=(const WindowIniFile& other) noexcept;
    WindowIniFile& operator=(WindowIniFile&& other) noexcept;

    bool contains(std::string_view name) const override;
    void initValue(std::string_view name, std::string_view value) override;

    std::vector<std::pair<std::string, std::string>> values() const override
    {
        std::vector<std::pair<std::string, std::string>> values;
        values.reserve(3);
        values.emplace_back(
            std::make_pair(ResolutionHeightLabel, std::to_string(m_resolutionHeight)));
        values.emplace_back(
            std::make_pair(ResolutionWidthLabel, std::to_string(m_resolutionWidth)));
        values.emplace_back(std::make_pair(WindowNameLabel, m_windowName));
        return values; 
    }

private:
    static constexpr std::string_view ResolutionWidthLabel {"ResolutionWidth"};
    static constexpr std::string_view ResolutionHeightLabel {"ResolutionHeight"};
    static constexpr std::string_view WindowNameLabel {"WindowName"};

    int m_resolutionWidth {1280};
    int m_resolutionHeight {720};
    std::string m_windowName {"MainWindow"};
};