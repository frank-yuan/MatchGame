//
//  GameEngine.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/26/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include "IUpdater.h"

struct GameEngineConfig
{
    std::string title;
    int width;
    int height;
    int fpsLimit;
    IUpdater& updater;
    
    GameEngineConfig(IUpdater& updater);
};

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    
    float Tick() const;
    
    bool Start(GameEngineConfig& config);
    void Quit();
    
    Uint32 GetLastFrameTick() const;
    
private:
    struct GameEngineImpl;
    std::unique_ptr<GameEngineImpl> mImpl;
};
#endif /* GameEngine_hpp */
