#pragma once
#include <utility>
#include "duration.h"
//Video items: MediaItems + resolution

class MediaItem {
protected:
	string artist;
	string title;
	string yt_link;
	Duration dur;
public:
	MediaItem(string _artist = "", string _title = "", string _yt_link = "", ushi _minutes=0, ushi _seconds=0) : artist{ _artist }, title{ _title }, dur{ Duration(_minutes, _seconds)}, yt_link{_yt_link} {};
	MediaItem(string _artist = "", string _title = "", string _yt_link = "", Duration _dur = Duration()) : artist{ _artist }, title{ _title }, dur{ _dur }, yt_link{ _yt_link } {};
	void setArtist(string _artist) { artist = _artist; };
	inline string getArtist() const { return artist; };
	inline string getTitle() const { return title; };
	inline string getYtLink() const { return yt_link; };
	inline const Duration& getDuration() { return dur; };
	friend ostream& operator<<(ostream& os, const MediaItem& mi);
	~MediaItem() = default;
};

class VideoItem : public MediaItem {
private:
	std::pair<ushi, ushi> res;
public:
	VideoItem(string _artist = "", string _title = "", string _yt_link = "", Duration _dur = Duration(), std::pair<int, int> _res = std::make_pair(0, 0)) : MediaItem{ _artist, _title, _yt_link, _dur }, res{ _res } {};
};