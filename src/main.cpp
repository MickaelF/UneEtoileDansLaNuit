#include "mainwindow.h"

#include "log.h"
#include "logger.h"
#include <exception>
#include <filesystem>
#include "path.h"
constexpr std::string_view companyName{ "PotatoThunder" };

int main(int argc, char* argv[])
{
    const auto dataPath {
        path::getDataPath(std::filesystem::path(argv[0]).stem().string(), companyName)};
    Logger logger(dataPath);
    BasicLog::setLogger(logger);
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
