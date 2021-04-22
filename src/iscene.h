#pragma once
#include "gameobject.h"

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
    IScene();
    virtual void render() = 0;

protected:
private:
    GameObject m_root;
};