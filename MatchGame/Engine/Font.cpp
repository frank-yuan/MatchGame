//
//  Font.cpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/2/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#include "Font.hpp"
#include <glm/gtx/transform.hpp>
#include <OpenGL/glu.h>
#include <memory>
#include <string>
#include "Texture.hpp"

const static int GLYPH_OFFSET = 31;
const static float FLOAT_PRECISION = 0.00001f;


struct Font::FontImpl
{
    
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
        
        GlyphInfo(Glyph& glyph, int texWidth, int texHeight)
        {
            minU = (float)glyph.x / texWidth;
            minV = (float)glyph.y / texHeight;
            maxU = (float)(glyph.x + glyph.w) / texWidth;
            maxV = (float)(glyph.y + glyph.h) / texHeight;
            width = glyph.w;
            height = glyph.h;
            offsetX = glyph.offsetX;
            offsetY = glyph.offsetY;
        }
    };
    
    const GlyphInfo* GetGlyphInfo(char c) const;
    std::vector<const GlyphInfo*> mGlyphInfo;
    std::shared_ptr<Texture> mTexture;
    float mScale;
    
    FontImpl(const std::vector<Glyph*>& config, std::shared_ptr<Texture> tex);
    
    void Render(const std::string& text, const glm::mat4& transform);
    void Render(const std::string& text, float x, float y, float scale, float rotation);
};


const Font::FontImpl::GlyphInfo* Font::FontImpl::GetGlyphInfo(char c) const
{
    int index = c - GLYPH_OFFSET;
    if (index < 0 || index >= mGlyphInfo.size())
        return NULL;
    return mGlyphInfo[index];
}

Font::FontImpl::FontImpl(const std::vector<Glyph*>& config, std::shared_ptr<Texture> tex)
: mGlyphInfo(256 - GLYPH_OFFSET, NULL)
, mTexture(tex)
, mScale(1.f)
{
    std::vector<Glyph*>::const_iterator cIter = config.begin();
    while (cIter != config.end())
    {
        Glyph* g = *cIter;
        assert(mGlyphInfo[g->id - GLYPH_OFFSET] == NULL);
        mGlyphInfo[g->id - GLYPH_OFFSET] = new GlyphInfo(*g, mTexture->Width(), mTexture->Height());
        ++cIter;
    }
    
}

void Font::FontImpl::Render(const std::string& text, float x, float y, float scale, float rotation)
{
    glm::mat4 mat;
    mat = glm::translate(mat, glm::vec3(x, y, 0.f));
    
    if (rotation)
        mat = glm::rotate(mat, rotation, glm::vec3(0.f, 0.f, 1.f));
    
    if (fabsf(scale - 1.0f) > FLOAT_PRECISION)
        mat = glm::scale(mat, glm::vec3(scale, scale, 1.f));
    
    Render(text, mat);
}


void Font::FontImpl::Render(const std::string& text, const glm::mat4& transform)
{
    if (text.length() == 0)
        return;
    glLoadMatrixf(reinterpret_cast<const float*>(&transform));

    glm::vec4 topLeft = glm::vec4(0, 0, 0, 1);
    glm::vec4 bottomRight = glm::vec4(0, 0, 0, 1);
    glBegin( GL_QUADS );
    mTexture->Bind();
    const char* textChar = text.c_str();
    
    char c;
    while ((c = *textChar++) != '\0')
    {
        const GlyphInfo* glyph = GetGlyphInfo(c);
        if (glyph)
        {
            topLeft.x += glyph->offsetX;
            topLeft.y += glyph->offsetY;
            
            bottomRight.x = topLeft.x + glyph->width * mScale;
            bottomRight.y = topLeft.y + glyph->height * mScale;
            
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


Font::Font(const std::vector<Glyph*>& config, std::shared_ptr<Texture> tex)
: mImpl(new FontImpl(config, tex))
{
}

void Font::Render(const std::string& text, float x, float y, float scale, float rotation)
{
    mImpl->Render(text, x, y, scale, rotation);
}

void Font::Render(const std::string& text, const glm::mat4& transform)
{
    mImpl->Render(text, transform);
}

void Font::SetScale(float scale)
{
    mImpl->mScale = scale;
}
