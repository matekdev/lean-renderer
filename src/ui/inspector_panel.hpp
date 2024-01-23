#pragma once

class GameObject;

class InspectorPanel
{
public:
    InspectorPanel();

    void Render(GameObject *&selectedModel);
};