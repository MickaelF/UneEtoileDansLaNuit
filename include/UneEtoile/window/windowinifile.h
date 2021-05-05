#pragma once
#include <pttk/file/abstractinidefinition.h>

#include <string>
#include <string_view>

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

    std::vector<std::pair<std::string, std::string>> values() const override;

private:
    int m_resolutionWidth {1280};
    int m_resolutionHeight {720};
    std::string m_windowName {"MainWindow"};
};