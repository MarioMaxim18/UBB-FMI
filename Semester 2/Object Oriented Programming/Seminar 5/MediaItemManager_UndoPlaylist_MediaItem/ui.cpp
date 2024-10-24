#include "ui.h"

void Console::printAllSongs(const vector<std::shared_ptr<MediaItem>>& allSongs) const
{
	for (const auto& song : allSongs) {
		cout << *song << endl;
		std::cout << "Number of shared_ptr objects referring to the same managed object: " << song.use_count() << std::endl;
	}
}

void Console::printAllSongs(const vector<MediaItem>& allSongs) const
{
	for (const auto& song : allSongs)
		cout << song << endl;
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

	this->srv.addMediaItem(artist, title, ytlink, mins, secs);
}

void Console::addVideoItemUI()
{
	string artist, title, ytlink, resolution;
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

	cout << "Resolution: ";

	getline(cin, resolution);

	

	this->srv.addMediaItem(artist, title, ytlink, mins, secs, resolution);
}


void Console::deleteSongUI() {
	string artist, title;

	cout << "Artist: ";
	getline(cin, artist);

	cout << "Title: ";
	getline(cin, title);

	this->srv.deleteSong(title, artist);
}

void Console::addByArtistAndTitleToPlaylistUI()
{
	
	string artist, title;

	cout << "Artist: ";
	getline(cin, artist);

	cout << "Title: ";
	getline(cin, title);
	this->srv.addSongByArtistAndTitleToPlaylist(title, artist);

}

void Console::addByArtistToPlaylistUI()
{
	string artist;

	cout << "Artist: ";
	getline(cin, artist);

	this->srv.addSongsByArtistToPlaylist(artist);

}

void Console::playPlaylistUI()
{
	this->srv.playSongsFromPlaylist();
}

void Console::emptyPlaylistUI()
{
	this->srv.emptyPlaylist();
}

void Console::undoUI() {
	srv.undo();
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
				this->addVideoItemUI();
				break;
			case 3:
				this->printAllSongs(this->srv.getAllSongs());
				break;
			case 4:
				this->deleteSongUI();
				break;
			case 5:
				this->undoUI();
				break;
			case 6:
				this->runPlaylist();
				break;
			case 0:
				return;
			default:
				cout << "Invalid option" << endl;
			}
		}
		catch (RepoException& e) {
			cout << e << '\n';
		}
		catch (std::runtime_error& e) {
			cout << e.what() << '\n';
		}
	}
}

void Console::runPlaylist()
{
	while (true) {
		int option;
		printPlaylistMenu();
		cin >> option;
		cin.ignore();
		try {
			switch (option) {
			case 1:
				this->addByArtistAndTitleToPlaylistUI();
				break;
			case 2:
				this->addByArtistToPlaylistUI();
				break;
			case 3:
				this->playPlaylistUI();
				break;
			case 4:
				this->emptyPlaylistUI();
				break;
			case 5:
				this->printAllSongs(this->srv.getAllFromPlaylist());
				break;
			case 6:
				return;
			default:
				cout << "Invalid option!" << endl;


			}
		}
		catch (RepoException& e) {
			cout << e << '\n';
		}
		catch (std::runtime_error& e) {
			cout << e.what() << '\n';
		}
	}
}


