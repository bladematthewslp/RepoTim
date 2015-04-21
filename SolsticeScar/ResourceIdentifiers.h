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
		Background_Woods,
		Background_Rounded,
		BloodAnimationA,
		GridBlockCrate,
		GreenOrb,
		LightningWall,
		PlayerHUD,
		PlayerHUDHealthbar,
		PlayerTransformEffect,
		RedOrb,
		RyobeDagger,
		RyobeParryEffect,
		RyobeHUD,
		RyobeHUDHealthbar,
		
		WoodsBackground,
		WoodsForeground,
		WoodsBackgroundComplete,

		TILE_BLANK,
		TILE_BRICK_WALL2_0_0,
		TILE_BRICK_WALL2_0_1,
		TILE_BRICK_WALL2_0_2,
		TILE_BRICK_WALL2_1_0,
		TILE_BRICK_WALL2_1_1,
		TILE_BRICK_WALL2_1_2,
		TILE_BRICK_WALL2_2_0,
		TILE_BRICK_WALL2_2_1,
		TILE_BRICK_WALL2_2_2,
		TILE_BRICK_WALL2_3_0,
		TILE_BRICK_WALL2_3_1,
		TILE_BRICK_WALL2_3_2,
		TILE_GROUND2,
		TILE_ROCK_WALL4,

		PROP_LIGHT_HANGING,
		PROP_SPIKES_LONG,
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
		PlayerTransformed,
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
		None,
		ChargeUp,
		DojiChopperStyle,
		DojiChopperStyleSoundEffect,
		DojiDead,
		DojiExpel,
		DojiHailBringerDescending,
		DojiHailBringerLanding,
		DojiHit,
		DojiImpact,
		DojiSwordSwing1,
		DojiSwordSwing2,
		DojiSwordSwing3,
		DojiSwordSwingAir,
		DojiSwordSwingQuick,
		DojiSwordSwingHit,
		DojiYouAreNotWorthy,
		ElectricCurrent,
		Jump,
		Landing,
		NinjaHit,
		NinjaDaggerSwing,
		NinjaSwordSwingHit,
		Running1,
		Running2,
		RyobeComeAndGetMe,
		RyobeDead,
		RyobeEmbracer,
		RyobeFellCrescent,
		RyobeFire,
		RyobeKnifeThrow,
		RyobeStandStill,
		RyobeSwordAttack,
		Teleport

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