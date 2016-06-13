#pragma once

#include "../Singleton.hpp"
#include "ScenePanel.hpp"

namespace XYGame
{
    class SceneWidget;
    class ScenePanel;
    class SceneManager : public Singleton<SceneManager>
    {

    public:
        template <typename T>
        static std::shared_ptr<T> CreateWidget(int panelId = 0)
        {
            T* widget = new T;
            widget->SetPanel(panelId);
            ScenePanel* panel = SceneManager::Instance()->InternalGetScenePanel(panelId);
            
            std::shared_ptr<T> result = std::shared_ptr<T>(widget);
            panel->AddWidget(result);
            
            return result;
        }
        
        
        SceneManager();
        ~SceneManager();

        
        void Render();

        int GetWidgetsCount() const;

    private:
        SceneManager(const SceneManager&);
        SceneManager& operator=(const SceneManager&);
        
        ScenePanel* InternalGetScenePanel(int panelId);

    private:
        typedef std::list<ScenePanel*> ScenePanelContainer;
        ScenePanelContainer mContainer;
    };
}