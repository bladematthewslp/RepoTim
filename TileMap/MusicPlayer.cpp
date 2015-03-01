#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
	: mMusic()
	, mFilenames()
	, mVolume(100.f)
	, mCurrentTheme(Music::None)
{
	mFilenames[Music::WoodsTheme] = "Music/WoodsTheme.ogg";
	mFilenames[Music::RyobeFightTheme] = "Music/RyobeBattleMusic.ogg";
}


void MusicPlayer::play(Music::ID theme)
{
	if(mCurrentTheme == theme)
		return;


	std::string filename = mFilenames[theme];
	if(!mMusic.openFromFile(filename) )
		throw std::runtime_error("Music " + filename + " could not be loaded.");
	mCurrentTheme = theme;
	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void MusicPlayer::stop()
{
	mMusic.stop();
	mCurrentTheme = Music::None;
}

void MusicPlayer::setPaused(bool paused)
{
	if(paused)
		mMusic.pause();
	else
		mMusic.play();


}


void MusicPlayer::setVolume(float volume)
{
	mVolume = volume;
}