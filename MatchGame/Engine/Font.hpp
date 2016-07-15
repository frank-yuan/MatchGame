//
//  Font.hpp
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 6/2/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef Font_hpp
#define Font_hpp

namespace XYGame
{

    struct GlyphInfo;
    class Texture;


    class Font
    {
    public:
        Font(const std::vector<std::vector<int> >& config, std::shared_ptr<Texture> tex);
        void Render(const std::string& text, float x, float y, float scale = 1.0f, float rotation = 0.f) const;
        void Render(const std::string& text, const glm::mat4& transform) const;
        ~Font();
    private:
        Font(const Font&);
        Font& operator=(const Font&);
        struct FontImpl;
        std::unique_ptr<FontImpl> mImpl;
    };
}
#endif /* Font_hpp */
