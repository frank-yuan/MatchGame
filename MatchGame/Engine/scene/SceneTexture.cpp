//
//  SceneTexture.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/08/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include "SceneWidget.hpp"
#include "SceneTexture.hpp"
#include <assert.h>

namespace XYGame
{
    SceneTexture::SceneTexture()
         : SceneWidget()
         //, mTex(King::Engine::Texture::TEXTURE_BACKGROUND)
    {
    }

    void SceneTexture::Render(){
        //GameEngine::Instance()->GetEngine().Render(mTex, GetTransform());
    };

    void SceneTexture::SetTexture(const string& texFileName)
    {
    //	assert(id >= King::Engine::Texture::TEXTURE_BACKGROUND && id < King::Engine::Texture::TEXTURE_MAX);
    //
    //	this->mTex = (King::Engine::Texture)id;
    //	this->mTextureCenter = glm::vec2(
    //		GameEngine::Instance()->GetEngine().GetTextureWidth(mTex) / 2.0f
    //		, GameEngine::Instance()->GetEngine().GetTextureHeight(mTex) / 2.0f);
    }

    string SceneTexture::GetTextureFileName() const
    {
        //return (int)this->mTex;
        return "";
    }

    glm::mat4& SceneTexture::GetTransform()
    {
        if (mIsDirty)
        {
            mTransform = glm::mat4(1.0f);
            mTransform = glm::translate(mTransform, glm::vec3(mLocation.x, mLocation.y, 0.0f));
            if (mRotation != 0.0f) {
                mTransform = glm::rotate(mTransform, mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            if (mScale != glm::vec2(1, 1))
            {
                mTransform = glm::translate(mTransform, glm::vec3(mTextureCenter.x, mTextureCenter.y, 0.0f));
                mTransform = glm::scale(mTransform, glm::vec3(mScale.x, mScale.y, 1.0f));
                mTransform = glm::translate(mTransform, glm::vec3(-mTextureCenter.x, -mTextureCenter.y, 0.0f));
            }
        }
        return mTransform;
    }

}