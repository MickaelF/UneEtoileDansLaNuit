#include "mainwindow.h"

#include "log.h"
#include "logger.h"
#include <exception>
#include <filesystem>

int main(int argc, char* argv[])
{
    Logger::setFolderPath(argv[0]);
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
