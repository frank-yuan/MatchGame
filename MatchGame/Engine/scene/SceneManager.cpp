#include "SceneManager.hpp"
#include "ScenePanel.hpp"

namespace XYGame
{
    
    SceneManager::SceneManager()
    {

    }

    SceneManager::~SceneManager()
    {
        for (ScenePanelContainer::iterator iter = mContainer.begin();
            iter != mContainer.end();
            ++iter)
        {
            delete (*iter);
        }
        mContainer.clear();
    }


    void SceneManager::Render()
    {
        for (ScenePanelContainer::const_iterator iter = mContainer.cbegin();
            iter != mContainer.cend();
            ++iter)
        {
            (*iter)->Render();
        }
    }

    int SceneManager::GetWidgetsCount() const
    {
        int count = 0;
        for (ScenePanelContainer::const_iterator iter = mContainer.cbegin();
            iter != mContainer.cend();
            ++iter)
        {
            count += (*iter)->GetWidgetsCount();
        }
        return count;
    }
    bool CompareScenePanel(ScenePanel* left, ScenePanel* right)
    {
        return left->GetPanelID() < right->GetPanelID();
    }

    ScenePanel* SceneManager::InternalGetScenePanel(int panelId)
    {
        ScenePanelContainer::iterator iter = mContainer.begin();
        while (iter != mContainer.end() && (*iter)->GetPanelID() < panelId)
        {
            ++iter;
        }

        if (iter != mContainer.end() && (*iter)->GetPanelID() == panelId)
        {
            return *iter;
        }
        else
        {
            ScenePanel* panel = new ScenePanel();
            panel->SetPanelID(panelId);
            mContainer.insert(iter, panel);
            return panel;
        }
    }
}
