
//#include <iostream>
#include <fstream>
#include <sstream>
#include "SceneManager.hpp"
#include "ScenePanel.hpp"
#include "../Font.hpp"


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


    void SceneManager::RenderScene()
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
    
    const Font* SceneManager::LoadFont(int fontId, const std::string& glyphPath, std::shared_ptr<Texture> tex)
    {
        if (mFontMap.find(fontId) != mFontMap.end())
            throw new std::runtime_error(std::string("Font exist"));
        if (tex.get() == NULL)
            throw new std::runtime_error(std::string("Font texture is NULL"));
        
        std::ifstream fin(glyphPath.c_str());
        std::string line;
        std::vector<int> lineValues;
        std::vector< std::vector<int> > glyphs;

        while (std::getline(fin, line))
        {
            std::stringstream ss(line);
            
            lineValues.clear();
            int v = 0;
            while (ss >> v)
            {
                lineValues.push_back(v);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            
            glyphs.push_back(lineValues);
        }
        
        mFontMap[fontId] = new Font(glyphs, tex);
        return mFontMap[fontId];

    }
    
    void SceneManager::UnloadFont(int fontId)
    {
        std::map<int, const Font*>::iterator iter = mFontMap.find(fontId);
        if (iter != mFontMap.end())
        {
            delete iter->second;
            mFontMap.erase(iter);
        }
    }
    
    
    const Font* SceneManager::GetFont(int fontId) const
    {
        std::map<int, const Font*>::const_iterator iter = mFontMap.find(fontId);
        if (iter != mFontMap.end())
        {
            return iter->second;
        }
        return NULL;
    }
}
