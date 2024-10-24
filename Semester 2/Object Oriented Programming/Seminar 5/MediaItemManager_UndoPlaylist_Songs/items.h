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
	//TO-DO: add all setters

	inline const string& getArtist() const { return artist; };
	inline const string& getTitle() const { return title; };
	inline const string& getYtLink() const { return yt_link; };
	inline const Duration& getDuration() const { return dur; } ;

	virtual string toString() const;
	
	//implement the operator in terms of the toString() method
	friend ostream& operator<<(ostream& os, const MediaItem& mi);
	friend bool operator==(const MediaItem& item1, const MediaItem& item2);
	
	virtual ~MediaItem() = default;

};

class VideoItem : public MediaItem {
private:
	std::pair<ushi, ushi> res;
	std::pair<ushi, ushi> processResolutionString(const std::string& resolution) const;
public:
	VideoItem(string _artist = "", string _title = "", string _yt_link = "", ushi _minutes = 0, ushi _seconds = 0, string _res = "0x0") : MediaItem{ _artist, _title, _yt_link, Duration(_minutes, _seconds) },res { processResolutionString(_res) } {};
	VideoItem(string _artist = "", string _title = "", string _yt_link = "", Duration _dur = Duration(), string _res = "0x0") : MediaItem{ _artist, _title, _yt_link, _dur }, res{ processResolutionString(_res) } {};
	string toString() const override;
	~VideoItem() = default;


};