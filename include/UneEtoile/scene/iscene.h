#pragma once
#include <UneEtoile/scene/gameobject.h>

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
    GameObject* root() { return &m_root; }

protected:
private:
    GameObject m_root;
};