//
//  SceneTexture.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/08/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include "SceneWidget.hpp"
#include "SceneTexture.hpp"
#include "../Texture.hpp"
#include <assert.h>
#include <OpenGL/glu.h>

namespace XYGame
{
    SceneTexture::SceneTexture()
         : SceneWidget()
         , mTex(NULL)
    {
    }

    void SceneTexture::Render(){
        glLoadMatrixf(reinterpret_cast<const float*>(&mTransform));
        
        glBegin( GL_QUADS );
        mTex->Bind();
        glTexCoord2f(0.f, 1.f);
        glVertex2f( -0.5f, -0.5f );
        glTexCoord2f(1.f, 1.f);
        glVertex2f( 0.5f, -0.5f );
        glTexCoord2f(1.f, 0.f);
        glVertex2f( 0.5f, 0.5f );
        glTexCoord2f(0.f, 0.f);
        glVertex2f( -0.5f, 0.5f );
        glEnd();
    };

    void SceneTexture::SetTexture(const string& texFileName)
    {
        mTex = Texture::LoadTexture(texFileName);
        assert(mTex.get() != NULL);
        
        	this->mTextureCenter = glm::vec2(
        		mTex->Width() / 2.0f
        		, mTex->Height() / 2.0f);
    }

    std::shared_ptr<Texture> SceneTexture::GetTexture() const
    {
        return mTex;
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