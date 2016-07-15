//
//  Font.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/2/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include <OpenGL/glu.h>
#include "Font.hpp"
#include "Texture.hpp"

namespace XYGame
{
    const static int GLYPH_OFFSET = 31;
    const static float FLOAT_PRECISION = 0.00001f;
    const static int GLYPH_DATA_SIZE = 7;
    
    struct GlyphInfo
    {
        float minU;
        float minV;
        float maxU;
        float maxV;
        int width;
        int height;
        int offsetX;
        int offsetY;
        
        GlyphInfo(const std::vector<int> glyph, int texWidth, int texHeight)
        {
            if (glyph.size() >= GLYPH_DATA_SIZE)
            {
                int index = 0;
                int x = glyph[++index];
                int y = glyph[++index];
                width = glyph[++index];
                height = glyph[++index];
                offsetX = glyph[++index];
                offsetY = glyph[++index];
                minU = (float)x / texWidth;
                minV = (float)y / texHeight;
                maxU = (float)(x + width) / texWidth;
                maxV = (float)(y + height) / texHeight;
            }
        }
    };


    struct Font::FontImpl
    {
       
        
        std::vector<const GlyphInfo*> mGlyphInfo;
        std::shared_ptr<Texture> mTexture;
        
        FontImpl(const std::vector<std::vector<int> >& config, std::shared_ptr<Texture> tex);
        ~FontImpl();
        
        const GlyphInfo* GetGlyphInfo(char c) const;
        void Render(const std::string& text, const glm::mat4& transform) const;
        void Render(const std::string& text, float x, float y, float scale, float rotation) const;
    };


    const GlyphInfo* Font::FontImpl::GetGlyphInfo(char c) const
    {
        int index = c - GLYPH_OFFSET;
        if (index < 0 || index >= mGlyphInfo.size())
            return NULL;
        return mGlyphInfo[index];
    }

    Font::FontImpl::FontImpl(const std::vector< std::vector<int> >& config, std::shared_ptr<Texture> tex)
    : mGlyphInfo(256 - GLYPH_OFFSET, NULL)
    , mTexture(tex)
    {
        std::vector< std::vector<int> >::const_iterator cIter = config.begin();
        while (cIter != config.end())
        {
            const std::vector<int>& g = *cIter;
            if (g.size() >= GLYPH_DATA_SIZE)
            {
                int id = g[0];
                mGlyphInfo[id - GLYPH_OFFSET] = new GlyphInfo(g, mTexture->Width(), mTexture->Height());
            }
            ++cIter;
        }
    }
    
    Font::FontImpl::~FontImpl()
    {
        for (int i = 0; i < mGlyphInfo.size(); ++i)
        {
            delete mGlyphInfo[i];
        }
    }

    void Font::FontImpl::Render(const std::string& text, float x, float y, float scale, float rotation) const
    {
        glm::mat4 mat;
        mat = glm::translate(mat, glm::vec3(x, y, 0.f));
        
        if (rotation)
            mat = glm::rotate(mat, rotation, glm::vec3(0.f, 0.f, 1.f));
        
        if (fabsf(scale - 1.0f) > FLOAT_PRECISION)
            mat = glm::scale(mat, glm::vec3(scale, scale, 1.f));
        
        Render(text, mat);
    }


    void Font::FontImpl::Render(const std::string& text, const glm::mat4& transform) const
    {
        if (text.length() == 0)
            return;
        glLoadMatrixf(reinterpret_cast<const float*>(&transform));

        glm::vec4 topLeft = glm::vec4(0, 0, 0, 1);
        glm::vec4 bottomRight = glm::vec4(0, 0, 0, 1);
        mTexture->Bind();
        glBegin( GL_QUADS );
        const char* textChar = text.c_str();
        
        char c;
        while ((c = *textChar++) != '\0')
        {
            const GlyphInfo* glyph = GetGlyphInfo(c);
            if (glyph)
            {
                topLeft.x += glyph->offsetX;
                topLeft.y += glyph->offsetY;
                
                bottomRight.x = topLeft.x + glyph->width;
                bottomRight.y = topLeft.y + glyph->height;
                
                // top left
                glTexCoord2f(glyph->minU, glyph->minV);
                glVertex2f(topLeft.x, topLeft.y);
                
                // bottom left
                glTexCoord2f(glyph->minU, glyph->maxV);
                glVertex2f(topLeft.x, bottomRight.y);
                
                // bottom right
                glTexCoord2f(glyph->maxU, glyph->maxV);
                glVertex2f(bottomRight.x, bottomRight.y);
                
                // top right
                glTexCoord2f(glyph->maxU, glyph->minV);
                glVertex2f(bottomRight.x, topLeft.y);
                
                
                topLeft.y -= glyph->offsetY;
                // move coord right
                topLeft.x = bottomRight.x;
            }
        }
        glEnd();
    }
    
    Font::Font(const std::vector<std::vector<int> >& config, std::shared_ptr<Texture> tex)
    : mImpl(new FontImpl(config, tex))
    {
    }
    
    Font::~Font()
    {
    }
    
    void Font::Render(const std::string& text, float x, float y, float scale, float rotation) const
    {
        mImpl->Render(text, x, y, scale, rotation);
    }
    
    void Font::Render(const std::string& text, const glm::mat4& transform) const
    {
        mImpl->Render(text, transform);
    }

}
