#include <UneEtoile/appinfo.h>
#include <UneEtoile/render/abstractrenderer.h>
#include <UneEtoile/window/mainwindow.h>
#include <pttk/log.h>
#include <pttk/logger.h>
#include <pttk/pttkpath.h>

#include <exception>
#include <filesystem>

#include "mainscene.h"

constexpr std::string_view companyName {"PotatoThunder"};

int main(int argc, char *argv[])
{
    std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path());
    AppInfo *info =
        AppInfo::instance(std::string(companyName),
                          std::filesystem::path(argv[0]).stem().string());
    const auto dataPath {
        pttkPath::getDataPath(info->appName(), info->companyName())};
    Logger logger(dataPath);
    BasicLog::setLogger(logger);
    std::unique_ptr<MainWindow> mainWindow;
    try
    {
        AbstractRenderer::selectRendererType(
            static_cast<AbstractRenderer::Type>(info->rendererIndex()));
        mainWindow = std::make_unique<MainWindow>();
    }
    catch (std::exception *e)
    {
        lFatal << e->what();
        return -1;
    }
    IScene *currentScene = new MainScene(mainWindow.get());
    while (currentScene)
    {
        currentScene->preRun();
        IScene *nextScene = currentScene->run();
        currentScene->postRun();
        if (nextScene != currentScene) currentScene = nextScene;
    }

    return 0;
}
