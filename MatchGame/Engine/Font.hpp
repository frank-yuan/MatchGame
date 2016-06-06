//
//  Font.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/2/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef Font_hpp
#define Font_hpp
#include <vector>
#include <memory>
#include <stdio.h>
#include <glm/glm.hpp>

struct Glyph
{
    int id;
    int x;
    int y;
    int w;
    int h;
};

struct GlyphInfo;
class Texture;


class Font
{
public:
    Font(const std::vector<Glyph*>& config, std::shared_ptr<Texture> tex);
    void Render(const std::string& text, float x, float y, float rotation = 0.f);
    void Render(const std::string& text, const glm::mat4& transform);
    inline void SetScale(float scale){mScale = scale;}
private:
    Font(const Font&);
    Font& operator=(const Font&);
    
    const GlyphInfo* GetGlyphInfo(char c) const;
    std::vector<const GlyphInfo*> mGlyphInfo;
    std::shared_ptr<Texture> mTexture;
    float mScale;
};
#endif /* Font_hpp */
