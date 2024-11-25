#include "TextureItem.h"
#include "Engine/EngineExtentions/Debug.h"
#include "Management/TextureManagement.h"
#include <filesystem>
TextureItem::TextureItem(std::string p)
{
    if (texture.loadFromFile(p)) {
        name = p.substr(p.find_last_of("/\\") + 1);
        size_t dotPos = name.find_last_of('.');
        if (dotPos != std::string::npos) {
            name = name.substr(0, dotPos);
        }


        std::string filename = std::filesystem::path(p).filename().string();
        size_t pos = filename.find('_'); // Find the underscore separating name and resolution
        if (pos != std::string::npos) {
            std::string resolutionPart = filename.substr(pos + 1); // Extract the part after '_'

            size_t xPos = resolutionPart.find('x'); // Look for the 'x' in the resolution
            if (xPos != std::string::npos) {
                int width = std::stoi(resolutionPart.substr(0, xPos)); // Extract width
                int height = std::stoi(resolutionPart.substr(xPos + 1)); // Extract height
                frameSize = sf::Vector2i(width, height);

                size_t pos = name.find('_');
                if (pos != std::string::npos) {
                    std::string resolutionPart = name.substr(pos);

                    name.erase(pos);
                }
            }
        }

        frameSize = TextureManagement::GetFrameSize(p);
        DebugLn("Successfully loaded texture: " << p);
    }
    else {
        DebugLn("Failed to load texture: " << p);
    }
    isSheet = texture.getSize().y > frameSize.y && frameSize != sf::Vector2i(0,0);
}

sf::Texture& TextureItem::GetTexture()
{
	return texture;
}

std::string& TextureItem::GetName()
{
	return name;
}

sf::Vector2i TextureItem::GetSize()
{
    return frameSize;
}

bool TextureItem::IsSheet()
{
    return isSheet;
}

