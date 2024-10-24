#pragma once

#include "repo.h"
#include <stack>
#include <memory>
#include "playlist.h"
#include "UndoAction.h"
class Service {
private:
	Repository& repo;
	std::stack<std::unique_ptr<UndoAction>> undoActions;

	Playlist playlist;
public:
	Service(Repository& repo) : repo{ repo } {};
	Service(const Service& other) = delete;
	void operator=(const Service& other) = delete;

	void addMediaItem(const string& artist, const string& title, const string& ytlink, const ushi& minutes, const ushi& seconds, const string& resolution="0x0");
	void deleteSong(string& artist, string& title);
	void undo();

	const vector<MediaItem>& getAllSongs() { return this->repo.getAllSongs(); };

	//Playlist operations
	void playSongsFromPlaylist();
	void addSongByArtistAndTitleToPlaylist(const string& title, const string& artist);
	void addSongsByArtistToPlaylist(const string& artist);
	void emptyPlaylist();

	const vector<MediaItem>& getAllFromPlaylist();
	
	~Service() = default;

};