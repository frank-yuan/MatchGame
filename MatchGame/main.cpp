//
//  main.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/25/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <OpenGL/glu.h>
#include <memory>
#include "Engine/Texture.hpp"
#include "Engine/GameEngine.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
GameEngine engine;
class UpdaterTemp : public IUpdater
{
    std::shared_ptr<Texture> tex;
    virtual void Update()
    {
        
        glEnable(GL_TEXTURE_2D);
        glClear( GL_COLOR_BUFFER_BIT );
        if (tex.get() == NULL)
            tex = Texture::LoadTexture("/Users/xyuan/Downloads/1.pic.jpg");

        glBegin( GL_QUADS );
        tex->Bind();
        glTexCoord2f(0.f, 1.f);
        glVertex2f( -0.5f, -0.5f );
        glTexCoord2f(1.f, 1.f);
        glVertex2f( 0.5f, -0.5f );
        glTexCoord2f(1.f, 0.f);
        glVertex2f( 0.5f, 0.5f );
        glTexCoord2f(0.f, 0.f);
        glVertex2f( -0.5f, 0.5f );
        glEnd();
        //std::cout << 1000.0f / engine.GetLastFrameTick() << std::endl;
    }
};
int main(int argc, const char * argv[]) {
    UpdaterTemp up;
    GameEngineConfig config(up);
    
    engine.Start(config);
    return 0;
}
