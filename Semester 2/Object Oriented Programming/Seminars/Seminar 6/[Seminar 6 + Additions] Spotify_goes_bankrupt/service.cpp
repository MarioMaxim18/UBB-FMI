#include <algorithm>
#include "service.h"

//void Service::playSongsFromPlaylist()
//{
//	playlist.playAllSongsFromPlaylist();
//}

void Service::addMediaItem(const string& artist, const string& title, const string& ytlink, const ushi& minutes, const ushi& seconds, const string& resolution)
{
	MediaItem item{ artist,title, ytlink, minutes, seconds };

	//TO-DO: add validations
	//TO-DO: add possibility of adding video item
	undoActions.push(std::make_unique<UndoAdd>(repo, item));

	this->repo.store(item);
	
}

void Service::deleteSong(string& artist, string& title) {
	const MediaItem& fmi = repo.find(artist, title);
	undoActions.push(std::make_unique<UndoDelete>(repo, fmi));
	repo.deleteItem(fmi);

	
}
const vector<MediaItem> Service::filterByTitle(string& title) {
	const vector<MediaItem>& allItems = repo.getAllSongs();
	vector<MediaItem> itemsWithTitle;

	std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(itemsWithTitle), [title](const MediaItem& item) {
		return item.getTitle().find(title)!=std::string::npos;
		});

	return itemsWithTitle;
}
void Service::undo() {
	if (undoActions.empty())
		throw std::runtime_error("There is no action to undo!");
	undoActions.top()->executeUndo();
	undoActions.pop();
}

void Service::playSongsFromPlaylist()
{
	playlist.playAllSongsFromPlaylist();
}

void Service::addSongByArtistAndTitleToPlaylist(const string& title, const string& artist)
{
	const MediaItem& item = repo.find(title, artist);
	playlist.addSong(item);
}

void Service::addSongsByArtistToPlaylist(const string& artist)
{
	const vector<MediaItem>& allItems = repo.getAllSongs();
	
	vector<MediaItem> itemsByArtist; 
		
	std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(itemsByArtist), [artist](const MediaItem& item) {
			return item.getArtist() == artist;
			});
	
	playlist.addMultipleSongs(itemsByArtist);
}

void Service::emptyPlaylist()
{
	playlist.emptyPlaylist();
}

const vector<MediaItem>& Service::getAllFromPlaylist() {
	return playlist.getAllPlaylistSongs();

}
