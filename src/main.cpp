#include "mainwindow.h"
#include "log.h"
#include "logger.h"
#include <exception>

void setExecutableName(std::string_view execPath) 
{
#ifdef WIN32
    constexpr char delimiter {'\\'};
#else
    constexpr char delimiter {'/'};
#endif
    auto lastSlash = execPath.find_last_of(delimiter)+1;
    auto lastDot = execPath.find_last_of('.');
    if (lastDot < lastSlash || lastDot == std::string_view::npos) lastDot = execPath.size();
    Logger::setFolderPath(execPath.substr(lastSlash, lastDot - lastSlash));
}

int main(int argc, char* argv[])
{
    setExecutableName(argv[0]);
    std::unique_ptr<MainWindow> mainWindow; 
    try
    {
        mainWindow = std::make_unique<MainWindow>(); 
    }
    catch (std::exception& e )
    {
        lFatal << e.what();
        return -1;
    }
    

    return mainWindow->show();
}
