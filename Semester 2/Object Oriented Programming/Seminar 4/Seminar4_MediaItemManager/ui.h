#pragma once
#include "service.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::getline;
class Console {
private:
	Service& srv;
	void printAllSongs(const vector<MediaItem*>& allSongs);
	void addSongUI();
	void playSongUI();
	static void printMenu() {
		cout << "Song Management" << endl;
		cout << "1. Add song." << endl;
		cout << "2. Print all songs" << endl;
		cout << "3. Play song" << endl;
		cout << "4. Exit" << endl;
	}
public:
	Console(Service& srv) :srv{ srv } {};
	void run();
};