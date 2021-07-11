#pragma once
#include <UneEtoile/imgui/widget/scenewidget.h>
#include <UneEtoile/scene/gameobject.h>

class MainWindow;

/* TODO :
    - Sauvegarde et ouverture de scene.
    - Widget Scene (arbre de Gameobjects) et GameObject (transform, shader,
   matériaux)
    - Scéne par défaut au démarrage
    - Sauvegarde des inputs utilisateurs pour pouvoir débugger
    - Créer une macro pour la déclaration des classes ImGui ?
*/

class IScene
{
public:
    IScene(MainWindow* window);
    GameObject* root() { return &m_root; }

    virtual void preRun() = 0;
    virtual IScene* run() = 0;
    virtual void postRun() = 0;

protected:
    GameObject m_root;
    MainWindow* m_window;

private:
    friend SceneWidget;
    SceneWidget m_widget;
};