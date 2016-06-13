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
        if (mEnableClip)
        {
            glScissor(mClipPosition.x, mClipPosition.y, mClipSize.x, mClipSize.y);
            glEnable(GL_SCISSOR_TEST);
        }
        else
        {
            glDisable(GL_SCISSOR_TEST);
        }
        for (SceneWidgetContainer::const_iterator iter = mContainer.begin();
            iter != mContainer.end();
            ++iter)
        {
            std::shared_ptr<SceneWidget> ptr = std::shared_ptr<SceneWidget>(*iter);
            ptr->Render();
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