#include "playlist.h"

const vector<MediaItem>& Playlist::getAllPlaylistSongs() const 
{
	return songs;
}

void Playlist::playAllSongsFromPlaylist()
{
	//adjust playSong code from previous iteration to play songs from playlist

}

void Playlist::addMultipleSongs(const vector<MediaItem>& items)
{
	songs.insert(songs.end(), items.begin(),items.end());
}

void Playlist::addSong(const MediaItem& item) {
	songs.push_back(item);
}

void Playlist::emptyPlaylist() {
	songs.clear();
}


