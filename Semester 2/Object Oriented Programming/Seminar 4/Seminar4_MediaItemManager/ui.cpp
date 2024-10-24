#include "ui.h"

void Console::printAllSongs(const vector<MediaItem*>& allSongs)
{
	for (const auto& song : allSongs)
		cout << *song;
}

void Console::addSongUI() {
	string artist, title, ytlink;
	ushi mins, secs;

	cout << "Artist: ";
	getline(cin, artist);

	cout << "Title: ";
	getline(cin, title);

	cout << "Minutes: ";
	cin >> mins;

	cout << "Seconds: ";
	cin >> secs;

	cin.ignore();

	cout << "Youtube link: ";

	getline(cin, ytlink);

	this->srv.addSong(artist, title, ytlink, mins, secs);
}

void Console::playSongUI()
{
	string artist, title;
	int mins, secs;

	cout << "Artist: ";
	getline(cin, artist);

	cout << "Title: ";
	getline(cin, title);

	this->srv.playSong(title, artist);
}

void Console::run()
{
	while (true) {
		int option;
		printMenu();
		cin >> option;
		cin.ignore();
		try {
			switch (option) {
			case 1:
				this->addSongUI();
				break;
			case 2:
				this->printAllSongs(this->srv.getAllSongs());
				break;
			case 3:
				this->playSongUI();
				break;
			case 4:
				return;
			default:
				cout << "Invalid option" << endl;
			}
		}
		catch (RepoException& e) {
			cout << e;
		}
	}
}


