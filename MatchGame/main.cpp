//
//  main.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/25/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <OpenGL/glu.h>
#include "Engine/Texture.hpp"
#include "Engine/Font.hpp"
#include "Engine/GameEngine.hpp"
#include "IUpdater.h"
#include "Engine/scene/SceneManager.hpp"
#include "Engine/scene/SceneTexture.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
using namespace std;
using namespace XYGame;
GameEngine engine;


class UpdaterTemp : public IUpdater
{
    Font* font;
    std::shared_ptr<Texture> tex;
    bool inited = false;
    std::shared_ptr<SceneTexture> st[4];
    void Init()
    {
        tex = Texture::LoadTexture("Resources/berlin_sans_demi_72_0.png");
        
        ifstream readStream;
        readStream.open("Resources/glyph.txt");
        std::vector<Glyph*> glyphs;
        char buff[128];
        if (readStream.is_open())
        {
            while (!readStream.eof())
            {
                readStream.getline(buff, 128);
                stringstream ss(buff);
                if (!ss.eof())
                {
                    Glyph* g = new Glyph();
                    int* pg = (int*)(g);
                    int v;
                    int imax = sizeof(Glyph) / sizeof(int);
                    int i = 0;
                    while (ss >> v && i++ < imax)
                    {
                        *pg++ = v;
                        if (ss.peek() == ',')
                            ss.ignore();
                    }
                    if (g->id > 0)
                        glyphs.push_back(g);
                    else
                        delete g;
                }
                
            }
        }
        readStream.close();
        font = new Font(glyphs, tex);
        // delete all glyphs
        for (int i = 0; i < glyphs.size(); ++i)
        {
            delete glyphs[i];
        }
        inited = true;
        

        st[0] = XYGame::SceneManager::CreateWidget<SceneTexture>(1);
        st[0]->SetTexture("Resources/A.png");
        st[1] = XYGame::SceneManager::CreateWidget<SceneTexture>(1);
        st[1]->SetTexture("Resources/C.png");
        st[2] = XYGame::SceneManager::CreateWidget<SceneTexture>(1);
        st[2]->SetTexture("Resources/P.png");
//        st[3] = XYGame::SceneManager::CreateWidget<SceneTexture>(0);
//        st[3]->SetTexture("Resources/back.png");
        
    }
    virtual void Update()
    {
        if (!inited)
            Init();
        
        glClear( GL_COLOR_BUFFER_BIT );
        
        SceneManager::Instance()->Render();
        font->Render("Hello, World!", 0 , 20, 0.1f);
        font->Render("abcdefg", 100 , 100, 0.5f);
        
        font->Render("Hello, World!", 200 , 200, 1, 3.14f/4);
        
        font->Render("hijklmn!", 300 , 300);


    }
};
int main(int argc, const char * argv[]) {
    UpdaterTemp up;
    GameEngineConfig config(up);
    config.width = SCREEN_WIDTH;
    config.height = SCREEN_HEIGHT;
   
    engine.Start(config);
    return 0;
}
