//
//  SceneWidget.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/08/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include "SceneWidget.hpp"

namespace XYGame
{
    SceneWidget::SceneWidget()
        : mLocation(0.f, 0.f)
        , mScale(1.f, 1.f)
        , mRotation(0)
        , mTransform(1.0f)
        , mPanel(0)
        , mDepth(0)
        , mIsDirty(true)
        , mActive(true)
    {
    }
    
    bool SceneWidget::operator < (const SceneWidget& rhs)
    {
        return mDepth < rhs.mDepth;
    }

    glm::mat4& SceneWidget::GetTransform()
    {
        if (mIsDirty)
        {
            mTransform = glm::mat4(1.0f);
            mTransform = glm::translate(mTransform, glm::vec3(mLocation.x, mLocation.y, 0.0f));
            if (mRotation != 0.0f) {
                mTransform = glm::rotate(mTransform, mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            mTransform = glm::scale(mTransform, glm::vec3(mScale.x, mScale.y, 1.0f));
        }
        return mTransform;
    }
}