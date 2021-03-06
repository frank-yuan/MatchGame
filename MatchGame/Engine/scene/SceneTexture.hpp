//
//  SceneTexture.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/08/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef SceneTexture_hpp
#define SceneTexture_hpp

#include "SceneWidget.hpp"

namespace XYGame {
    
    class Texture;

    class SceneWidget;
    
    class SceneTexture : public SceneWidget
    {
    public:
        void SetTexture(const std::string& texFileName);
        std::shared_ptr<Texture> GetTexture() const;
        void Render();

        virtual glm::mat4& GetTransform();
    protected:
        SceneTexture();
    private:
        SceneTexture(const SceneTexture&);
        SceneTexture& operator=(const SceneTexture&);

        
    private:
        std::shared_ptr<Texture> mTex;
        glm::vec2 mScaleCenter;

        friend class SceneManager;
    };
    
}

#endif