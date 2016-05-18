//
//  GameEngine.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/26/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#include "GameEngine.hpp"

GameEngineConfig::GameEngineConfig(IUpdater& inUpdater)
    :updater(inUpdater)
    , title("")
    , width(640)
    , height(480)
    , fpsLimit(60)
{
}

struct GameEngine::GameEngineImpl
{
    
    SDL_Window* window;
    SDL_GLContext context;
    Uint32 lastTick;
    bool quit;
    
    GameEngineImpl();
    bool Init(const std::string& title, int width, int height);
    void Close();
private:
    bool InitGL();
    

};

GameEngine::GameEngineImpl::GameEngineImpl()
    : window(NULL)
    , lastTick(0)
    , quit(false)
{
}

bool GameEngine::GameEngineImpl::Init(const std::string& title, int width, int height)
{
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Use OpenGL 2.1
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
        
        //Create window
        window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create context
            context = SDL_GL_CreateContext( window );
            if( context == NULL )
            {
                printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Use Vsync
                if( SDL_GL_SetSwapInterval( 1 ) < 0 )
                {
                    printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
                }
                
                //Initialize OpenGL
                if( !InitGL() )
                {
                    printf( "Unable to initialize OpenGL!\n" );
                    success = false;
                }
            }
        }
    }
    return success;
}

bool GameEngine::GameEngineImpl::InitGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;
    
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
    
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
    
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
    
    return success;
}

void GameEngine::GameEngineImpl::Close()
{
    //Destroy window
    SDL_DestroyWindow( window );
    
    //Quit SDL subsystems
    SDL_Quit();
}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin( GL_QUADS );
    glVertex2f( -0.5f, -0.5f );
    glVertex2f( 0.5f, -0.5f );
    glVertex2f( 0.5f, 0.5f );
    glVertex2f( -0.5f, 0.5f );
    glEnd();

}

GameEngine::GameEngine()
: mImpl(new GameEngineImpl)
{
    
}

GameEngine::~GameEngine()
{
    
}

bool GameEngine::Start(GameEngineConfig &config)
{
    //Initialization flag
    bool success = mImpl->Init(config.title, config.width, config.height);
    
    if (success)
    {
        Uint32 frameTick = (Uint32)(1000.0f / config.fpsLimit);
        Uint32 startTick = SDL_GetTicks();
        Uint32 lastTick = 0;
        //Event handler
        SDL_Event e;
        while (!mImpl->quit)
        {
            lastTick = startTick;
            startTick = SDL_GetTicks();
            mImpl->lastTick = startTick - lastTick;
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    mImpl->quit = true;
                }
            }
            
            config.updater.Update();
            
            //Update screen
            SDL_GL_SwapWindow( mImpl->window );
            Uint32 tickDiff = SDL_GetTicks() - startTick;
            if (tickDiff < frameTick)
            {
                SDL_Delay(frameTick - tickDiff);
            }
        }
        mImpl->Close();
    }
    
    return success;
}


void GameEngine::Quit()
{
    mImpl->quit = true;
}

float GameEngine::Tick() const
{
    return 0;
}

Uint32 GameEngine::GetLastFrameTick() const
{
    return mImpl->lastTick;
}
