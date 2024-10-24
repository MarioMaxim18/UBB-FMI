
#pragma once
#include <string>
#include <ostream>
#include <istream>
using std::istream;
using std::ostream;
using std::string;

class MediaItem
{
protected:
	string m_title;
	string m_artist;
	string m_path;
public:
	MediaItem(string title, string artist, string path);
	MediaItem() = default;
	virtual string toString() const;
	bool operator==(const MediaItem& other) {
		return this->getArtist() == other.getArtist() && this->getTitle() == other.getTitle() && this->m_path == other.m_path;
	}
	friend ostream& operator<<(ostream& os, const MediaItem&);
	friend istream& operator>>(istream& os, MediaItem&);
	string getTitle() const {
		return m_title;
	}
	string getArtist()const {
		return m_artist;
	}
};
class VideoItem :public MediaItem {
private://the default modifier is private
	string m_resolution;
public:
	VideoItem(string title, string artist, string path, string resolution);
	string toString() const override;
	VideoItem() = default;
};