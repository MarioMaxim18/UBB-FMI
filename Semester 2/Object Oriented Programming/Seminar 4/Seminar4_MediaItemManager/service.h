#pragma once
#include <windows.h>
#include <shellapi.h>
#include "repo.h"
class Service {
private:
	Repository& repo;
public:
	Service(Repository& repo) : repo{ repo } {};
	void addSong(const string& artist, const string& title, const string& ytlink, const ushi& minutes, const ushi& seconds);
	void playSong(const string& title, const string& artist);
	const vector<MediaItem*>& getAllSongs() { return this->repo.getAllSongs(); };

};