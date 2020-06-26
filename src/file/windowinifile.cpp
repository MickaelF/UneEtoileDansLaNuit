#include "windowinifile.h"
#include <string>

namespace 
{
const char* ResolutionWidthLabel {"ResolutionWidth"};
const char* ResolutionHeightLabel {"ResolutionHeight"};
const char* WindowNameLabel {"WindowName"};
} // namespace

WindowIniFile::WindowIniFile(const WindowIniFile& other) noexcept
    : m_resolutionHeight(other.m_resolutionHeight),
      m_resolutionWidth(other.m_resolutionWidth),
      m_windowName(other.m_windowName)
{
}

WindowIniFile::WindowIniFile(WindowIniFile&& other) noexcept
    : m_resolutionHeight(other.m_resolutionHeight),
      m_resolutionWidth(other.m_resolutionWidth),
      m_windowName(other.m_windowName)
{
    other.m_resolutionHeight = 0; 
    other.m_resolutionWidth = 0;
    other.m_windowName.clear();
}

WindowIniFile& WindowIniFile::operator=(const WindowIniFile& move) noexcept
{
    m_resolutionHeight = move.m_resolutionHeight;
    m_resolutionWidth = move.m_resolutionWidth;
    m_windowName = move.m_windowName;
    return *this;
}

WindowIniFile& WindowIniFile::operator=(WindowIniFile&& move) noexcept
{
    m_resolutionHeight = move.m_resolutionHeight;
    m_resolutionWidth = move.m_resolutionWidth;
    m_windowName = move.m_windowName;

    move.m_resolutionHeight = 0;
    move.m_resolutionWidth = 0;
    move.m_windowName.clear();
    return *this;
}

bool WindowIniFile::contains(std::string_view name) const
{
    return name == ResolutionWidthLabel || name == ResolutionHeightLabel || name == WindowNameLabel;
}

void WindowIniFile::initValue(std::string_view name, std::string_view value)
{
    if (name == ResolutionWidthLabel)
        m_resolutionWidth = std::stoi(std::string(value));
    else if (name == ResolutionHeightLabel)
        m_resolutionHeight = std::stoi(std::string(value));
    else if (name == WindowNameLabel)
        m_windowName = value;
}
