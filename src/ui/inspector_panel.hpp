#pragma once

class Model;

class InspectorPanel
{
public:
    InspectorPanel();

    void Render(Model *&selectedModel);
};