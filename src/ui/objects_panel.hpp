#pragma once

#include <vector>

class GameObject;

class ObjectsPanel
{
public:
    ObjectsPanel();

    void Render(std::vector<GameObject> &gameObjects, GameObject *&selectedGameObject);
};