#include "TextureLoader.h"

#include "Engine/EngineExtentions/Debug.h"
#include "TextureItem.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

TextureLoader::TextureLoader()
{
	std::string unitPath = "Assets/Units";
	std::string uiPath = "Assets/UI";
    LoadTextures(unitPath);
    LoadTextures(uiPath);
    LoadSpriteSheets();
}

void TextureLoader::LoadTextures(std::string& path)
{
    for (const auto& entry : fs::directory_iterator(path)) {
        std::string filePath = entry.path().string();

        if (filePath.size() >= 4 &&
            (filePath.compare(filePath.size() - 4, 4, ".png") == 0 ||
                filePath.compare(filePath.size() - 4, 4, ".jpg") == 0))
        {
            AddTexture(filePath);
        }
    }
}

void TextureLoader::LoadSpriteSheets()
{
    for (TextureItem& texture : GetLoadedTextures()) {
        if (texture.IsSheet()) {
            AddSpriteSheet(texture);
        }
    }
}

void TextureLoader::AddTexture(std::string p)
{
	loadedTextures.emplace_back(p);
}

sf::Texture& TextureLoader::GetTexture(std::string name)
{
    for (TextureItem& texture : GetLoadedTextures()) {
        std::string textureName = texture.GetName();
        size_t pos = textureName.find('_');
        if (pos != std::string::npos) {
            std::string resolutionPart = textureName.substr(pos);

            textureName.erase(pos);
        }
        if (name.compare(textureName) == 0) {
            return texture.GetTexture();
        }
    }
    DebugLn("unsuccessful return of texture: " << name);
}
TextureItem& TextureLoader::GetTextureItem(std::string name)
{
    for (TextureItem& texture : GetLoadedTextures()) {
        std::string textureName = texture.GetName();
        size_t pos = textureName.find('_');
        if (pos != std::string::npos) {
            std::string resolutionPart = textureName.substr(pos);

            textureName.erase(pos);
        }
        if (name.compare(textureName) == 0) {
            return texture;
        }
    }
    DebugLn("unsuccessful return of texture: " << name);
}

void TextureLoader::AddSpriteSheet(TextureItem& t)
{
    spriteSheets.emplace_back(t);
}

SpriteSheet& TextureLoader::GetSpriteSheet(std::string name)
{
    for (SpriteSheet& sheet : GetSpriteSheets()) {
        std::string sheetName = sheet.GetName();
        if (name.compare(sheetName) == 0) {
            return sheet;
        }
    }
    DebugLn("unsuccessful return of texture: " << name);
}

std::vector<TextureItem>& TextureLoader::GetLoadedTextures()
{
    return loadedTextures;
}
std::vector<SpriteSheet>& TextureLoader::GetSpriteSheets()
{
    return spriteSheets;
}
