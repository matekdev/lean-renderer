#pragma once

#include <vector>

class Model;

class ObjectsPanel
{
public:
    ObjectsPanel();

    void Render(std::vector<Model> &models, Model *&selectedModel);
};