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
    std::shared_ptr<Texture> tex;
    bool inited = false;
    std::shared_ptr<SceneTexture> st[4];
    void Init()
    {
        tex = Texture::LoadTexture("Resources/berlin_sans_demi_72_0.png");
        SceneManager::Instance()->LoadFont(0, std::string("Resources/glyph.txt"), tex);

        inited = true;
        

        st[0] = XYGame::SceneManager::CreateWidget<SceneTexture>(1);
        st[0]->SetTexture("Resources/A.png");
        st[0]->SetPosition(200, 400);
        st[1] = XYGame::SceneManager::CreateWidget<SceneTexture>(1);
        st[1]->SetTexture("Resources/C.png");
        st[1]->SetPosition(120, 120);
        st[1]->SetScale(.5f, .5f);
        st[2] = XYGame::SceneManager::CreateWidget<SceneTexture>(1);
        st[2]->SetTexture("Resources/C.png");
        st[2]->SetPosition(320, 320);
        
    }
    
    int frame = 0;
    virtual void Update()
    {
        if (!inited)
            Init();
        
        ++frame;
        
        glClear( GL_COLOR_BUFFER_BIT );

        SceneManager::Instance()->RenderScene();
        const Font* font = SceneManager::Instance()->GetFont(0);
        if (font)
        {
            font->Render("Hello, World!", 0 , 20, 0.1f);
            font->Render("abcdefg", 100 , 100, 0.5f);
            
            font->Render("Hello, World!", 200 , 200, 1, 3.14f/4);

            font->Render("hijklmn!", 300 , 300);
        }
        if (frame == 100)
        {
            st[2].reset();
        }
        if (frame == 200)
            st[1].reset();

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
