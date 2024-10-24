#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "items.h"
#include <windows.h>
#include <shellapi.h>
#include <vector>
using std::vector;
class Playlist {
private:
	//We assume only songs (basic MediaItems) can be included in a playlist
	vector<std::shared_ptr<MediaItem>> songs;
public:
	Playlist()=default;
	const vector<std::shared_ptr<MediaItem>>& getAllPlaylistSongs() const;
	void playAllSongsFromPlaylist();
	void addSong(std::shared_ptr<MediaItem> item);
	void addMultipleSongs(const vector< std::shared_ptr<MediaItem>>& items);
	void emptyPlaylist();
	~Playlist() = default;

};
