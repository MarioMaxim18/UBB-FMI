#include <algorithm>
#include "service.h"

void Service::playSongsFromPlaylist()
{
	playlist.playAllSongsFromPlaylist();
}

void Service::addMediaItem(const string& artist, const string& title, const string& ytlink, const ushi& minutes, const ushi& seconds, const string& resolution)
{

	//TO-DO: add validations
	std::shared_ptr<MediaItem> item;
	std::cout << "Number of shared_ptr objects referring to the same managed object: " << item.use_count() << std::endl;

	if (resolution == "0x0")
		item = std::make_shared<MediaItem>(artist, title, ytlink, minutes, seconds);
	else
		item = std::make_shared<VideoItem>(artist, title, ytlink, minutes, seconds, resolution);

	std::cout << "Number of shared_ptr objects referring to the same managed object: " << item.use_count() << std::endl;

	this->repo.store(item);
	std::cout << "Number of shared_ptr objects referring to the same managed object: " << item.use_count() << std::endl;

	undoActions.push(std::make_unique<UndoAdd>(repo, item));
	std::cout << "Number of shared_ptr objects referring to the same managed object: " << item.use_count() << std::endl;

}

void Service::deleteSong(string& artist, string& title) {
	const std::shared_ptr<MediaItem> fmi = repo.find(artist, title);
	repo.deleteItem(*fmi);
	std::cout << fmi->getArtist() << " " << fmi->getTitle() << std::endl;
	undoActions.push(std::make_unique<UndoDelete>(repo, fmi));

	
	
}

void Service::undo() {
	if (undoActions.empty())
		throw std::runtime_error("There is no action to undo!");
	undoActions.top()->executeUndo();
	undoActions.pop();
}

void Service::addSongByArtistAndTitleToPlaylist(const string& title, const string& artist)
{
	std::shared_ptr<MediaItem> item = repo.find(title, artist);
	playlist.addSong(item);
}

void Service::addSongsByArtistToPlaylist(const string& artist)
{
	const vector<std::shared_ptr<MediaItem>>& allItems = repo.getAllSongs();
	
	vector<std::shared_ptr<MediaItem>> itemsByArtist;
		
	std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(itemsByArtist), [artist](const std::shared_ptr<MediaItem> item) {
			return item->getArtist() == artist;
			});
	
	
	playlist.addMultipleSongs(itemsByArtist);
}

void Service::emptyPlaylist()
{
	playlist.emptyPlaylist();
}

const vector<std::shared_ptr<MediaItem>>& Service::getAllFromPlaylist() {
	return playlist.getAllPlaylistSongs();

}
