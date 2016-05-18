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
#include "Engine/GameEngine.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
GameEngine engine;
class UpdaterTemp : public IUpdater
{
    virtual void Update()
    {
        glClear( GL_COLOR_BUFFER_BIT );
        
        glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f( 0.5f, -0.5f );
        glVertex2f( 0.5f, 0.5f );
        glVertex2f( -0.5f, 0.5f );
        glEnd();
        std::cout << 1000.0f / engine.GetLastFrameTick() << std::endl;
    }
};
int main(int argc, const char * argv[]) {
    UpdaterTemp up;
    GameEngineConfig config(up);
    
    engine.Start(config);
    return 0;
}
