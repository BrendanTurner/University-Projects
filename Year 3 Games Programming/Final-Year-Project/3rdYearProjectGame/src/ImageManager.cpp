#pragma once
#include "ImageManager.h"

sf::Image& ImageManager::getImage(const std::string& image)
{
	auto iter = m_images.find(image);
	if (iter != std::end(m_images))
	{
		return iter->second;
	}
	else
	{
		m_images[image] = sf::Image();
		m_images[image].loadFromFile("assets/images/" + image + ".png");//check image type
		m_images[image].createMaskFromColor(sf::Color(255, 255, 255));
		return(getImage(image));
	}

	return m_images[image];
}
