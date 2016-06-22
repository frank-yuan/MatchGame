//
//  SceneWidget.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/08/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef SceneWidget_hpp
#define SceneWidget_hpp

using namespace std;

namespace XYGame
{
    
    class ScenePanel;
    class SceneWidget
    {
    public:
        virtual ~SceneWidget(){}
        inline glm::vec2 GetPosition() const {return mLocation;}
        inline void SetPosition(glm::vec2& pos) {mLocation = pos; mIsDirty = true;}
        inline void SetPosition(float x, float y) {mLocation = glm::vec2(x, y); mIsDirty = true;}
        
        inline glm::vec2 GetScale() const {return mScale;}
        inline void SetScale(glm::vec2& scale) {mScale = scale; mIsDirty = true;}
        inline void SetScale(float x, float y) {mScale = glm::vec2(x, y); mIsDirty = true;};

        inline float GetRotation() const {return mRotation;}
        inline void SetRotation(float rot){mRotation = rot; mIsDirty = true;}
        
        inline bool IsActive() const {return mActive;}
        inline void SetActive(bool active) {mActive = active;}

        inline int GetPanelID() const {return mPanel;}
        
        inline void SetDepth(int depth) { mDepth = depth;}
        
        bool operator < (const SceneWidget& rhs);

        virtual glm::mat4& GetTransform();

        virtual void Render() = 0;
        
    protected:
        SceneWidget();
    private:
        SceneWidget(const SceneWidget&);
        SceneWidget& operator=(const SceneWidget&);
        
        void SetPanel(int panelID){mPanel = panelID;}

    protected:
        glm::vec2 mLocation;
        glm::vec2 mScale;
        int mDepth;
        float mRotation;
        int mPanel;
        glm::mat4 mTransform;
        bool mIsDirty;
        bool mActive;

        friend class SceneManager;
    };
}
#endif