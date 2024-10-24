#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "items.h"
#include <windows.h>
#include <shellapi.h>
#include <vector>
using std::vector;
class Playlist {
private:
	vector<MediaItem> songs;
public:
	Playlist()=default;
	void addSong(const MediaItem& item);
	void addMultipleSongs(const vector<MediaItem>& items);
	void emptyPlaylist();
	void playAllSongsFromPlaylist();

	const vector<MediaItem>& getAllPlaylistSongs() const;
	~Playlist() = default;

};
