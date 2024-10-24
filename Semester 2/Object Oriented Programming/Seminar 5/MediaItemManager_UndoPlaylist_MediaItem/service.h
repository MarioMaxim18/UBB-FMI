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
	void addMediaItem(const string& artist, const string& title, const string& ytlink, const ushi& minutes, const ushi& seconds, const string& resolution="0x0");
	const vector<std::shared_ptr<MediaItem>>& getAllSongs() { return this->repo.getAllSongs(); };
	void deleteSong(string& artist, string& title);
	void undo();
	~Service() = default;

	//Playlist operations
	void playSongsFromPlaylist();
	void addSongByArtistAndTitleToPlaylist(const string& title, const string& artist);
	void addSongsByArtistToPlaylist(const string& artist);
	void emptyPlaylist();

	const vector<std::shared_ptr<MediaItem>>& getAllFromPlaylist();
	
};