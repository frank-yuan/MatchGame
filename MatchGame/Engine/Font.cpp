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

struct GlyphInfo
{
    float minU;
    float minV;
    float maxU;
    float maxV;
    int width;
    int height;
    
    GlyphInfo(Glyph& glyph, int texWidth, int texHeight)
    {
        minU = (float)glyph.x / texWidth;
        minV = (float)glyph.y / texHeight;
        maxU = (float)(glyph.x + glyph.w) / texWidth;
        maxV = (float)(glyph.y + glyph.h) / texHeight;
        width = glyph.w;
        height = glyph.h;
    }
};

Font::Font(const std::vector<Glyph*>& config, std::shared_ptr<Texture> tex)
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

void Font::Render(const std::string& text, float x, float y, float rotation)
{
    glm::mat4 mat;
    mat = glm::translate(mat, glm::vec3(x, y, 0.f));
    if (rotation)
    {
        mat = glm::rotate(mat, rotation, glm::vec3(0.f, 0.f, 1.f));
    }

    Render(text, mat);
}

void Font::Render(const std::string& text, const glm::mat4& transform)
{
    if (text.length() == 0)
        return;
    glLoadMatrixf(reinterpret_cast<const float*>(&transform));

    glm::vec4 coordTopLeft = glm::vec4(0, 0, 0, 1);
    glm::vec4 coordBottomRight = glm::vec4(0, 0, 0, 1);
    glBegin( GL_QUADS );
    mTexture->Bind();
    const char* textChar = text.c_str();
    char c;
    glm::vec4 coordCache[2];
    while ((c = *textChar++) != '\0')
    {
        const GlyphInfo* glyph = GetGlyphInfo(c);
        if (glyph)
        {
            coordBottomRight.x = coordTopLeft.x + glyph->width * mScale;
            coordBottomRight.y = glyph->height * mScale;
            
            coordCache[0] = coordTopLeft;
            coordCache[1] = coordBottomRight;
            
            // top left
            glTexCoord2f(glyph->minU, glyph->minV);
            glVertex2f(coordCache[0].x, coordCache[0].y);
            
            // bottom left
            glTexCoord2f(glyph->minU, glyph->maxV);
            glVertex2f(coordCache[0].x, coordCache[1].y);
            
            // bottom right
            glTexCoord2f(glyph->maxU, glyph->maxV);
            glVertex2f(coordCache[1].x, coordCache[1].y);
            
            // top right
            glTexCoord2f(glyph->maxU, glyph->minV);
            glVertex2f(coordCache[1].x, coordCache[0].y);
            
            // move coord right
            coordTopLeft.x = coordBottomRight.x;
        }
    }
    glEnd();


}


const GlyphInfo* Font::GetGlyphInfo(char c) const
{
    int index = c - GLYPH_OFFSET;
    if (index < 0 || index >= mGlyphInfo.size())
        return NULL;
    return mGlyphInfo[index];
}