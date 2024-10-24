#include "repo.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
using std::endl;



void Repository::loadData() {
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
			MediaItem item{ artist, title, yt_link, duration };
			this->items.push_back(item);
		}
		
	}
	fin.close();
}

void Repository::saveData()
{
	std::ofstream fout(filename);
	for (const auto& item : this->items) {
		string line = item.toString() + "\n";
		fout << line;
	}

}

bool Repository::exists(const MediaItem& item) const
{
	try {
		this->find(item.getTitle(), item.getArtist());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}


void Repository::store(const MediaItem& song)
{
	
	if (exists(song))
		throw RepoException("There is already a media item with this title and artist.\n");
	this->items.push_back(song);
	this->saveData();

	
}

const MediaItem& Repository::find(const string& titlu, const string& artist) const
{
	//can use find_if
    for (const auto& song : this->items) {
        if (song.getTitle() == titlu && song.getArtist() == artist)
            return song;
    }
    throw RepoException("There is no song with this title and artist.\ns");
}

void Repository::deleteItem(const MediaItem& item) {
	auto itr = std::find_if(items.begin(), items.end(), [&item](const MediaItem& other) {
		return item == other;
		});
	if (itr == items.end()) 
		throw RepoException("There is not a media item with this title and artist.\n");
	items.erase(itr);
	this->saveData();
}

Repository::~Repository() {
	
}


ostream& operator<<(ostream& stream, const RepoException& exception)
{
    stream << exception.errorMsg;
    return stream;
}

