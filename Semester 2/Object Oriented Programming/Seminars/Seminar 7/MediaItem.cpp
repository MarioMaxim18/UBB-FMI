#include "MediaItem.h"
#include <vector>
#include <sstream>
using namespace std;


MediaItem::MediaItem(string title, string artist, string path)
{
	m_title = title;
	m_artist = artist;
	m_path = path;
}

string MediaItem::toString() const
{

	return m_title + ",  " + m_artist + ",  " + m_path;
}

ostream& operator<<(ostream& os, const MediaItem& m)
{
	os << m.toString();
	return os;
}

vector<string> tokenize(string str, char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}



istream& operator>>(istream& is, MediaItem& m)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');

	if (tokens.size() != 3) // make sure all the starship data was valid
		return is;

	m.m_title = tokens[0];
	m.m_artist = tokens[1];
	m.m_path = tokens[2];

	return is;


}

VideoItem::VideoItem(string title, string artist, string path, string resolution) :MediaItem(title, artist, path), m_resolution(resolution)
{

}

string VideoItem::toString() const
{
	return MediaItem::toString() + ", resolution: " + m_resolution;
}
