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
    int offsetX;
    int offsetY;
};

struct GlyphInfo;
class Texture;


class Font
{
public:
    Font(const std::vector<Glyph*>& config, std::shared_ptr<Texture> tex);
    void Render(const std::string& text, float x, float y, float scale = 1.0f, float rotation = 0.f);
    void Render(const std::string& text, const glm::mat4& transform);
    void SetScale(float scale);
private:
    Font(const Font&);
    Font& operator=(const Font&);
    struct FontImpl;
    std::unique_ptr<FontImpl> mImpl;
};
#endif /* Font_hpp */
