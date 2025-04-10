#include "repo.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
using std::endl;



void Repository::loadData() {
	//Example line: 
	//Deep Purple, Smoke on the Water, 5:40, https://www.youtube.com/watch?v=Q2FzZSBD5LE
	//Options to get the tokens delimited by ',', ":"
	// line = line from file
	// Returns the index of the first occurence of the substring in str
	// size_t find (const string& str, size_t pos = 0);
	// and variations: find_last/first_of, find_last/first_not_of,... 
	// Removes characters starting from pos
	//string& string ::erase (size_type pos)
	//-Throw out_of_range if idx > size().

	//returns the string starting from pos, of length len
	//string substr (size_t pos, size_t len) const;

	//std::getline(input_stream, str, delimiter);

	//can also use istringstream/sstringstream

	std::ifstream fin(filename);
	std::string line;
	std::string token;
	std::string artist;
	std::string title;
	Duration duration;
	std::string yt_link;
	std::string resolution;
	int index = 0;
	while (std::getline(fin, line)) {
		index = 0;
		std::istringstream iss{line};
		while (std::getline(iss, token, ',')) {
			
			//strip prefixing and suffixing whitespace
			token.erase(token.find_last_not_of(' ') + 1);        
			token.erase(0, token.find_first_not_of(' '));
			
			if (index == 0) {
				artist = token;
			}
			if (index == 1) {
				title = token;
			}
			if (index == 2) {
				duration = Duration(token);
			}
			if (index == 3) {
				yt_link = token;
			}
			if (index == 4) {
				resolution = token;
			}
			index++;

		}
		if (index != 0) {
			if (index == 4) {
				std::shared_ptr<MediaItem> item = std::make_shared<MediaItem>(artist, title, yt_link, duration);
				this->items.push_back(item);
			}
			else if (index == 5){
				std::shared_ptr<MediaItem> item = std::make_shared<VideoItem>(artist, title, yt_link, duration, resolution);
				this->items.push_back(item);
			}
			else {
				//throw an exception, invalid data
			}
		}
	}
	fin.close();
}

void Repository::saveData()
{
	std::ofstream fout(filename);
	for (const auto& item : this->items) {
		string line = item->toString() + "\n";
		fout << line;
	}

}

bool Repository::exists(const std::shared_ptr<MediaItem> item) const
{
	try {
		this->find(item->getTitle(), item->getArtist());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}


void Repository::store(std::shared_ptr<MediaItem> song)
{
	
	if (exists(song))
		throw RepoException("There is already a media item with this title and artist.\n");
	this->items.push_back(song);
	this->saveData();

	
}

const std::shared_ptr<MediaItem> Repository::find(const string& titlu, const string& artist) const
{
    for (const auto& song : this->items) {
        if (song->getTitle() == titlu && song->getArtist() == artist)
            return song;
    }
    throw RepoException("There is no song with this title and artist.\ns");
}

void Repository::deleteItem(const MediaItem& item) {
	auto itr = std::find_if(items.begin(), items.end(), [&item](const std::shared_ptr<MediaItem> other) {
		return item == *other;
		});
	if (itr == items.end()) 
		throw RepoException("There is not a media item with this title and artist.\n");
	items.erase(itr);
	this->saveData();
}

Repository::~Repository() {
	/*for (auto mi : items) {
		delete mi;
	}*/
}


ostream& operator<<(ostream& stream, const RepoException& exception)
{
    stream << exception.errorMsg;
    return stream;
}


