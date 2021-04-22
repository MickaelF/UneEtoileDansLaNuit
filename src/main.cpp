#include <pttk/log.h>
#include <pttk/logger.h>
#include <pttk/pttkpath.h>

#include <exception>
#include <filesystem>

#include "appinfo.h"
#include "mainwindow.h"
constexpr std::string_view companyName {"PotatoThunder"};

int main(int argc, char* argv[])
{
    AppInfo& info =
        AppInfo::instance(std::filesystem::path(argv[0]).stem().string(),
                          std::string(companyName));
    const auto dataPath {pttkPath::getDataPath(info.appName, info.companyName)};
    Logger logger(dataPath);
    BasicLog::setLogger(logger);
    std::unique_ptr<MainWindow> mainWindow;
    try
    {
        mainWindow = std::make_unique<MainWindow>();
    }
    catch (std::exception& e)
    {
        lFatal << e.what();
        return -1;
    }

    return mainWindow->show();
}
