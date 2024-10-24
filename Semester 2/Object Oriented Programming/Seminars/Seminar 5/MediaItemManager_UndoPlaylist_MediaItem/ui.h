#pragma once
#include "service.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::getline;
class Console {
private:
	//TO-DO: add success messages/informative messages for user for each operation
	Service& srv;
	void printAllSongs(const vector<std::shared_ptr<MediaItem>>& allSongs) const ;
	void printAllSongs(const vector<MediaItem>& allSongs) const;
	void addSongUI();
	void addVideoItemUI();
	static void printMenu() {
		cout << "Song Management" << endl;
		cout << "1. Add song." << endl;
		cout << "2. Add video item" << endl;
		cout << "3. Print all songs" << endl;
		cout << "4. Delete song" << endl;
		cout << "5. Undo action" << endl;
		cout << "6. Playlist actions" << endl;
		cout << "0. Exit" << endl;
	}
	static void printPlaylistMenu() {
		cout << "Playlist menu:" << endl;
		cout << "1. Add song by title and artist to playlist." << endl;
		cout << "2. Add songs by artist to playlist." << endl;
		cout << "3. Play songs from playlist." << endl;
		cout << "4. Empty playlist." << endl;
		cout << "5. Print playlist." << endl;
		cout << "6. Back to main menu." << endl;
	}
	void deleteSongUI();
	void addByArtistToPlaylistUI();
	void addByArtistAndTitleToPlaylistUI();
	void playPlaylistUI();
	void emptyPlaylistUI();
	void undoUI();
public:
	Console(Service& srv) :srv{ srv } {};
	void run();
	void runPlaylist();
};