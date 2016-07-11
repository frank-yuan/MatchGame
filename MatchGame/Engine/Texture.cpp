//
//  Texture.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/29/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2_image/SDL_image.h>
#include <OpenGL/glu.h>
#include "Texture.hpp"

using namespace std;

namespace XYGame
{
    shared_ptr<Texture> Texture::LoadTexture(const string & path)
    {
        static map<const string, weak_ptr<Texture> > cache;
        shared_ptr<Texture> sp = cache[path].lock();
        if (!sp)
            cache[path] = sp = shared_ptr<Texture>(new Texture(path));
        return sp;
    }

    Texture::Texture(const string & filename)
    : mSurface(IMG_Load(filename.c_str()), SDL_FreeSurface)
    , mTextureId(new unsigned int, &DeleteTexture)
    , mPath(filename){
        cout << "Loading Texture" << filename << endl;
        if (mSurface == nullptr) {
            throw std::runtime_error(std::string("Unable to load texture ") + filename);
        }
        glGenTextures(1, mTextureId.get());
        glBindTexture(GL_TEXTURE_2D, *mTextureId);
        int mode;
        
        
        switch (mSurface->format->BytesPerPixel) {
            case 4:
            {
                mode = GL_RGBA;
                
#if __LITTLE_ENDIAN__
                // For Mac, the pixel format we loaded is not RGBA
                SDL_PixelFormat pf(*mSurface->format);
                pf.palette = 0;
                pf.BitsPerPixel = 32;
                pf.BytesPerPixel = 4;
                pf.Rshift = pf.Rloss = pf.Gloss = pf.Bloss = pf.Aloss = 0;
                pf.Rmask = 0x000000ff;
                pf.Gshift = 8;
                pf.Gmask = 0x0000ff00;
                pf.Bshift = 16;
                pf.Bmask = 0x00ff0000;
                pf.Ashift = 24;
                pf.Amask = 0xff000000;
                
                mSurface = std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>(SDL_ConvertSurface(mSurface.get(), &pf, SDL_SWSURFACE), SDL_FreeSurface);
#endif
                break;
            }
            case 3:
                mode = GL_RGB;
                break;
            case 1:
                mode = GL_LUMINANCE_ALPHA;
                break;
            default:
                throw std::runtime_error("Image with unknown channel profile");
                break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, mode, mSurface->w, mSurface->h, 0, mode, GL_UNSIGNED_BYTE, mSurface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    Texture::~Texture()
    {
#if DEBUG
        std::cout << "Deleting texture" << mPath << std::endl;
#endif
    }

    void Texture::DeleteTexture(unsigned int* textureId) {
        glDeleteTextures(1, textureId);
    }

    void Texture::Bind() {
        glBindTexture(GL_TEXTURE_2D, *mTextureId);
    }

    int Texture::Width() const {
        return mSurface->w;
    }

    int Texture::Height() const {
        return mSurface->h;
    }

    Texture::operator SDL_Surface*() {
        return mSurface.get();
    }
}