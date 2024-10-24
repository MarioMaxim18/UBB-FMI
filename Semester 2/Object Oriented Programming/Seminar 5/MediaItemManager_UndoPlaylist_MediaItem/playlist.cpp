#include "playlist.h"

const vector<std::shared_ptr<MediaItem>>& Playlist::getAllPlaylistSongs() const
{
	return songs;
}

void Playlist::playAllSongsFromPlaylist()
{
	//adjust playSong code from previous iteration to play songs from playlist

}

void Playlist::addMultipleSongs(const vector<std::shared_ptr<MediaItem>>& items)
{
	songs.insert(songs.end(), items.begin(),items.end());
}

void Playlist::addSong(std::shared_ptr<MediaItem> item) {
	songs.push_back(item);
	std::cout << "Number of shared_ptr objects referring to the same managed object: " << item.use_count() << std::endl;

}

void Playlist::emptyPlaylist() {
	songs.clear();
}


