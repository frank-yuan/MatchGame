//
//  ScenePanel.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/08/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include <OpenGL/gl3.h>
#include "ScenePanel.hpp"
#include "SceneWidget.hpp"

using namespace std;

namespace XYGame
{
    ScenePanel::ScenePanel()
        : mEnableClip(false)
        , mClipPosition(glm::ivec2(0, 0))
        , mClipSize(glm::ivec2(0, 0))
    {
    }

    void ScenePanel::AddWidget(shared_ptr<SceneWidget> widget)
    {
        mContainer.insert(widget);
    }

    void ScenePanel::Render()
    {
        static std::shared_ptr<SceneWidget> cachedPtr;
        if (mEnableClip)
        {
            glScissor(mClipPosition.x, mClipPosition.y, mClipSize.x, mClipSize.y);
            glEnable(GL_SCISSOR_TEST);
        }
        else
        {
            glDisable(GL_SCISSOR_TEST);
        }
        for (SceneWidgetContainer::iterator iter = mContainer.begin();
            iter != mContainer.end();)
        {
            if (iter->expired())
            {
                iter = mContainer.erase(iter);
                continue;
            }
            else
            {
                cachedPtr = iter->lock();
                cachedPtr->Render();
            }
            ++iter;
        }
    }

    void ScenePanel::EnableClip(glm::ivec2 position, glm::ivec2 size)
    {
        mEnableClip = true;
        mClipPosition = position;
        mClipSize = size;
    }

    void ScenePanel::DisableClip()
    {
        mEnableClip = false;
        mClipPosition = glm::ivec2(0, 0);
        mClipSize = glm::ivec2(0, 0);
    }

    ScenePanel::~ScenePanel()
    {
        assert(mContainer.size() == 0);
    }
}