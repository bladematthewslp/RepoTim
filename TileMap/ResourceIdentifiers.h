#pragma once

namespace sf
{
	class Texture;
	class Font;
	class Image;
	class SoundBuffer;
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

namespace Music
{
	enum ID
	{
		None,
		WoodsTheme,
		RyobeFightTheme,

	};

}

namespace SoundEffect
{
	enum ID
	{
		DojiSwordSwing1,
		DojiSwordSwing2,
		DojiSwordSwingQuick,
		DojiSwordSwing3,
		DojiSwordSwingHit,
		NinjaSwordSwing,
		NinjaSwordSwingHit

	};


}

namespace Buttons
{
	enum ID
	{
		ResumeNormal,
		ResumeSelected,
		QuitNormal,
		QuitSelected,
		ControlsNormal,
		ControlsSelected,
		PlayNormal,
		PlaySelected
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Texture, Buttons::ID>	ButtonHolder;
typedef ResourceHolder<sf::Image, Images::ID>		ImageHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;
//typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;