#define _CRT_SECURE_NO_WARNINGS

#include "service.h"

void Service::addSong(const string& artist, const string& title, const string& ytlink, const ushi& minutes, const ushi& seconds)
{
	MediaItem* s = new MediaItem{ artist,title, ytlink, minutes, seconds };
	this->repo.store(s);
}

void Service::playSong(const string& title, const string& artist)
{
	const MediaItem* foundSong = this->repo.find(title, artist);
	string ytlink = foundSong->getYtLink();

	std::wstring output;
	size_t outputSize = ytlink.size() + 1; // +1 for null terminator
	output.resize(outputSize);
	mbstowcs(&output[0], ytlink.c_str(), outputSize);
	ShellExecute(0, 0, output.c_str(), 0, 0,SW_SHOW);

}
