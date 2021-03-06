//
//  Texture.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/29/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

struct SDL_Surface;
namespace XYGame
{
    class Texture
    {
    public:
        static std::shared_ptr<Texture> LoadTexture(const std::string & filename);
        operator SDL_Surface*();
        ~Texture();

        int Width() const;
        int Height() const;
        void Bind();
        
    private:
        Texture(const std::string & filename);
        Texture(const Texture& );        Texture& operator= (const Texture&);
        static void DeleteTexture(unsigned int* textureId);
        
    private:
        std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> mSurface;
        std::unique_ptr<unsigned int,void(*)(unsigned int*)> mTextureId;
        std::string mPath;;
    };
}
#endif /* Texture_hpp */
