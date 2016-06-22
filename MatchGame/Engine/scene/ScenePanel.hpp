//
//  ScenePanel.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/08/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef ScenePanel_hpp
#define ScenePanel_hpp

namespace XYGame
{
    class SceneWidget;
    
    template <class T>
    struct wptr_pointer_less_than
    {
        bool operator() ( const std::weak_ptr<T>& lhs, const std::weak_ptr<T>& rhs ) const {
            return lhs.expired() || (!rhs.expired() && lhs.lock().get() < rhs.lock().get());
        }
    };
    
    class ScenePanel
    {
    public:
        ScenePanel();
        ~ScenePanel();
        int GetPanelID() const {return mID;}
        size_t GetWidgetsCount() const {return mContainer.size();}
        void EnableClip(glm::ivec2 position, glm::ivec2 size);
        void DisableClip();
    
    private:
        ScenePanel(const ScenePanel&);
        ScenePanel& operator=(const ScenePanel&);
        inline void SetPanelID(int panelId){mID = panelId;}

        void AddWidget(const std::shared_ptr<SceneWidget>& widget);
        void Render();


    private:
        int mID;
        
        typedef std::set<std::weak_ptr<SceneWidget>, wptr_pointer_less_than<SceneWidget> > SceneWidgetContainer;
        SceneWidgetContainer mContainer;
        
        bool mEnableClip;
        glm::ivec2 mClipPosition;
        glm::ivec2 mClipSize;

        friend class SceneManager;
    };
}
#endif