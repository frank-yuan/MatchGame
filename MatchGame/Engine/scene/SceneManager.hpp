#pragma once

#include "../Singleton.hpp"
#include "ScenePanel.hpp"

namespace XYGame
{
    class Texture;
    class Font;
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

        
        void RenderScene();

        int GetWidgetsCount() const;
        
        const Font* LoadFont(int fontId, const std::string& glyphPath, std::shared_ptr<Texture> tex);
        void UnloadFont(int fontId);
        
        const Font* GetFont(int fontId) const;

    private:
        SceneManager(const SceneManager&);
        SceneManager& operator=(const SceneManager&);
        
        ScenePanel* InternalGetScenePanel(int panelId);

    private:
        typedef std::list<ScenePanel*> ScenePanelContainer;
        ScenePanelContainer mContainer;
        std::map<int, const Font*> mFontMap;
    };
}