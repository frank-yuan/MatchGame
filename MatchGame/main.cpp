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
#include "Engine/Font.hpp"
#include "Engine/GameEngine.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
using namespace std;
GameEngine engine;


class UpdaterTemp : public IUpdater
{
    Font* font;
    std::shared_ptr<Texture> tex;
    bool inited = false;
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
        inited = true;
        
    }
    virtual void Update()
    {
        if (!inited)
            Init();
        
        glClear( GL_COLOR_BUFFER_BIT );
        font->Render("Hello, World!", 100 , 100, 3.14f/4);

        
//        glBegin( GL_QUADS );
//        tex->Bind();
//        glTexCoord2f(0.f, 1.f);
//        glVertex2f( -0.5f, -0.5f );
//        glTexCoord2f(1.f, 1.f);
//        glVertex2f( 0.5f, -0.5f );
//        glTexCoord2f(1.f, 0.f);
//        glVertex2f( 0.5f, 0.5f );
//        glTexCoord2f(0.f, 0.f);
//        glVertex2f( -0.5f, 0.5f );
//        glEnd();
        //std::cout << 1000.0f / engine.GetLastFrameTick() << std::endl;
    }
};
int main(int argc, const char * argv[]) {
    UpdaterTemp up;
    GameEngineConfig config(up);
   
    engine.Start(config);
    return 0;
}
