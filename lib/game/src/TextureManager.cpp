#include <zeno/Game/TextureManager.hpp>
#include <cassert>

namespace ze {

	bool TextureManager::loadTexture(const std::string& _texturePath, const std::string& _textureName) {
		Texture* texture = new Texture();
		if (texture->loadFromFile(_texturePath)) {
			m_Textures[_textureName] = texture;
			return true;
		}
		delete texture;
		return false;
	}
	bool TextureManager::loadTextureFiles(const std::string& _texturePath, const std::string& _textureName) {
		Texture* texture = new Texture();
		if (texture->loadTexture(_texturePath)) {
			m_Textures[_textureName] = texture;
			return true;
		}
		return false;
	}
	bool TextureManager::createTexture(const std::string& _textureName) {
		auto& t = getTexture(_textureName);
		if (!t.isLoaded()) {
			return t.createTexture();
		}

		return false;
	}
	Texture& TextureManager::getTexture(const std::string& _textureName) {
		return *(*m_Textures.find(_textureName)).second;
	}
	const Texture& TextureManager::getTexture(const std::string& _textureName) const {
		return *(*m_Textures.find(_textureName)).second;
	}

	bool TextureManager::createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo) {
		const unsigned startingSize = 32;
		return createAtlas(_atlasName, _subtextureInfo, startingSize);
	}
	bool TextureManager::createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo, unsigned _startingSize) {
		unsigned size = _startingSize;
		ze::Image atlas;
		std::vector<std::pair<ze::Image, std::string>> imageNames;

		for (const auto& info : _subtextureInfo) {
			auto& ip = imageNames.emplace_back();
			ip.second = info.first;
			if (!ip.first.loadFromFile(info.second)) {
				return false;
			}
		}

		bool valid = false;
		while (size <= MaxAtlasSize) {
			atlas.create(size, size, ze::Colour::Magenta);

			if (tryCreateAtlasImage(_atlasName, atlas, imageNames)) {
				valid = true;
				break;
			}

			std::cerr << "Failed to create atlas '" << _atlasName << "' with dimensions " << size << "x" << size << std::endl;

			size *= 2;
		}

		if (!valid) {
			return false;
		}

		Texture* texture = new Texture();
		if (texture->loadFromImage(atlas)) {
			m_Textures[_atlasName] = texture;
			return true;
		}

		m_TextureAtlasInfo.erase(m_TextureAtlasInfo.find(_atlasName));
		delete texture;
		return false;
	}

	ze::FloatRect TextureManager::getAtlasSubTextureRect(const std::string& _atlasName, const std::string& _subTextureName) const {
		const auto& atlasInfo = m_TextureAtlasInfo.at(_atlasName);
		return atlasInfo.at(_subTextureName);
	}

	bool TextureManager::tryCreateAtlasImage(const std::string& _atlasName, ze::Image& _atlas, const std::vector<std::pair<ze::Image, std::string>>& _imageNamePairs) {
		std::unordered_map<std::string, ze::FloatRect> atlasInfo;

		assert(_atlas.getSize().x == _atlas.getSize().y);
		const unsigned size = _atlas.getSize().x;

		unsigned spacing = 1;
		unsigned currentX = spacing;
		unsigned currentY = spacing;
		unsigned maximumY = 0;

		for (const auto& inp : _imageNamePairs) {
			const auto& image = inp.first;
			const ze::Vector2u s = image.getSize();

			if (currentX + s.x + spacing > size) {
				// We are too wide, need to go to the next row
				currentX = spacing;
				currentY = maximumY;
			}

			if (currentY + s.y + spacing > size) {
				// We are too high, run out of room
				return false;
			}

			for (unsigned iy = 0; iy < s.y; ++iy) {
				for (unsigned ix = 0; ix < s.x; ++ix) {
					_atlas.setPixel(currentX + ix, currentY + iy, image.getPixel(ix, iy));
				}
			}

			ze::FloatRect bounds = ze::FloatRect(
				(static_cast<float>(currentX) + 0.5f) / static_cast<float>(size),
				1.0f - ((static_cast<float>(currentY) - 0.5f) / static_cast<float>(size)) - static_cast<float>(s.y) / static_cast<float>(size),
				static_cast<float>(s.x - 1) / static_cast<float>(size),
				static_cast<float>(s.y - 1) / static_cast<float>(size)
			);

			atlasInfo[inp.second] = bounds;

			maximumY = std::max(maximumY, currentY + s.y + spacing);
			currentX += s.x + spacing;
		}

		m_TextureAtlasInfo[_atlasName] = atlasInfo;

		return true;
	}
}
