//
//  Texture.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/29/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include "Texture.hpp"

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <OpenGL/glu.h>


Texture::Texture(const char* filename)
: mSurface(IMG_Load(filename), SDL_FreeSurface)
, mTextureId(new unsigned int, &DeleteTexture) {
    if (mSurface == nullptr) {
        throw std::runtime_error(std::string("Unable to load texture ") + filename);
    }
    glGenTextures(1, mTextureId.get());
    glBindTexture(GL_TEXTURE_2D, *mTextureId);
    int mode;
    switch (mSurface->format->BytesPerPixel) {
        case 4:
            mode = GL_RGBA;
            break;
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