#include "Texture.h"

#include <stdexcept>

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::cache;

Texture::Texture(const std::string& fileLocation) : textureID(0) {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

std::shared_ptr<Texture> Texture::get(std::string name) {
	auto it = cache.find(name);

	if (it == cache.end()) {
		it = cache.emplace(name, std::make_shared<Texture>(name)).first;
	}

	return it->second;
}

Texture::Texture(Texture&& tex) noexcept : textureID(tex.textureID) {
	tex.textureID = 0;
}

Texture& Texture::operator=(Texture&& tex) noexcept {
	using std::swap;
	swap(textureID, tex.textureID);
	return *this;
}

void Texture::useTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbindAll() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}