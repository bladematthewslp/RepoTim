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
		HealthBar0,
		HealthBar10,
		HealthBar20,
		HealthBar30,
		HealthBar40,
		HealthBar50,
		HealthBar60,
		HealthBar70,
		HealthBar80,
		HealthBar90,
		HealthBar100,
		PlayerHUD,
		PlayerHUDHealthbar,
		PlayerMugshot,
		RyobeHUD,
		RyobeHUDHealthbar,
		RyobeMugshot,


	};
}

namespace Images
{
	enum ID
	{
		BloodAnimationA,
		GreenOrb,
		GridBlockCrate,
		LightningWall,
		Ninja,
		Parry,
		Player,
		RedOrb,
		Ryobe,
		RyobeDagger,
		
		
		
	};

}



// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Image, Images::ID>		ImageHolder;
//typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;