#ifndef INCLUDED_ZENO_GAME_TEXTURE_MANAGER_HPP_
#define INCLUDED_ZENO_GAME_TEXTURE_MANAGER_HPP_

#include <zeno/Core/Rect.hpp>
#include <zeno/Graphics/Texture.hpp>
#include <unordered_map>

namespace ze {

    class TextureManager {
    public:
        bool loadTexture(const std::string& _texturePath, const std::string& _textureName);

        bool loadTextureFiles(const std::string& _texturePath, const std::string& _textureName);
        bool createTexture(const std::string& _textureName);

        Texture& getTexture(const std::string& _textureName);
        const Texture& getTexture(const std::string& _textureName) const;

        bool createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo);
        bool createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo, unsigned _startingSize);

        ze::FloatRect getAtlasSubTextureRect(const std::string& _atlasName, const std::string& _subTextureName) const;

    private:
        bool tryCreateAtlasImage(const std::string& _atlasName, ze::Image& _atlas, const std::vector<std::pair<ze::Image, std::string>>& _imageNamePairs);

        static constexpr const unsigned MaxAtlasSize{ 4096 };

    private:
        std::unordered_map<std::string, Texture*> m_Textures;
        std::unordered_map<std::string, std::unordered_map<std::string, ze::FloatRect>> m_TextureAtlasInfo;
    };

}

#endif // INCLUDED_ZENO_GAME_TEXTURE_MANAGER_HPP_