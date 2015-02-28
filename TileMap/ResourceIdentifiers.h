#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		BloodAnimationA,
		GridBlockCrate,
		GreenOrb,
		LightningWall,
		PlayerHUD,
		PlayerHUDHealthbar,
		RedOrb,
		RyobeDagger,
		RyobeParryEffect,
		RyobeHUD,
		RyobeHUDHealthbar,
		WoodsBackground,
		WoodsForeground,
		WoodsBackgroundComplete

	};
}

namespace Images
{
	enum ID
	{
		BloodAnimationA,
		//GreenOrb,
		//LightningWall,
		Ninja,
		//Parry,
		Player,
		//RedOrb,
		Ryobe,
		
		
		
	};

}



// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Image, Images::ID>		ImageHolder;
//typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;