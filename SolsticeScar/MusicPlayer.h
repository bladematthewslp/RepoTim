#pragma once
#include "ResourceIdentifiers.h"
#include <SFML/Audio/Music.hpp>

#include <map>
class MusicPlayer
{

	public:
		MusicPlayer();
		void		play(Music::ID theme);
		void		stop();

		void		setPaused(bool paused);
		void		setVolume(float volume);

	private:

		sf::Music	mMusic;
		std::map<Music::ID, std::string>	mFilenames;
		float		mVolume;
		Music::ID	mCurrentTheme;

};