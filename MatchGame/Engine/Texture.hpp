//
//  Texture.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/29/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <memory>

struct SDL_Surface;

class Texture
{
public:
    Texture(const char* filename);
    operator SDL_Surface*();

    int Width() const;
    int Height() const;
    void Bind();
private:
    Texture(const Texture& );
    Texture& operator= (const Texture&);
    static void DeleteTexture(unsigned int* textureId);
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> mSurface;
    std::unique_ptr<unsigned int,void(*)(unsigned int*)> mTextureId;
};
#endif /* Texture_hpp */
