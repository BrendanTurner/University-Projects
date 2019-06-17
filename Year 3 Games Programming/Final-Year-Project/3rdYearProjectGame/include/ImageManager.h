#pragma once
#include<SFML/Graphics.hpp>
#include <unordered_map>
class ImageManager
{
public:
	sf::Image& getImage(const std::string& image);
private:
	std::unordered_map<std::string, sf::Image> m_images;
};