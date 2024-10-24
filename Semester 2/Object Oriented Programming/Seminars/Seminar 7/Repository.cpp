#include "Repository.h"
#include<algorithm> // only here i use functions from it
#include<ostream>
#include<fstream>
#include<assert.h>
#include<iostream>

void Repository::remove(const MediaItem& song)
{
    //begin - iterator to the first element
// end - iterator after the last element

    /*std::vector<MediaItem>::iterator it=...*/
    auto it= find_if(songs.begin(), songs.end(), [song](const MediaItem& s)->bool {
            return (song.getTitle() == s.getTitle() && song.getArtist() == s.getArtist());
        });
    if (it == songs.end()) {
        throw RepoException("Song not found!" + song.toString());
    }
    songs.erase(it);
}

std::vector<MediaItem>& Repository::getSongs()
{
	return songs;
}

void Repository::add(const MediaItem& newSong)
{
	songs.push_back(newSong);
}


const MediaItem& Repository::find(std::string title, std::string artist) const noexcept(false)
{
	auto it = find_if(songs.begin(), songs.end(), [title, artist](const MediaItem& s)->bool {
		return title == s.getTitle() && artist == s.getArtist();
		});
	if (it == songs.end()) {
		throw RepoException("Find song not found!");
	}
	return *it;
}

void FileRepository::save()
{
	std::ofstream outfile{ path };
	if (!outfile.is_open()) {
		throw RepoException("Cannot open file!");
	}
	outfile << "Title, Artist, Path";
	for (auto s : songs) {
		outfile << s << std::endl;
	}
	outfile.close();
}

void FileRepository::load()
{
	songs.clear();
	std::ifstream infile{ path };
	if (!infile.is_open()) {
		throw RepoException("Cannot open file!");
	}
	MediaItem m;
	while (infile >> m)
		songs.push_back(m);

}

void FileRepository::add(const MediaItem& newSong)
{
	Repository::add(newSong);
	save();
}

void FileRepository::remove(const MediaItem& song)
{
	Repository::remove(song);
	save();
}



void RepoTester::testAdd()
{
	Repository r;
	MediaItem m("Starboy", "The Weeknd", "https://www.youtube.com/watch?v=Rif-RTvmmss");
	r.add(m);
	assert(r.getSongs().at(0) == m);

}

void RepoTester::testFind()
{
	Repository r;

	MediaItem m("Starboy", "The Weeknd", "https://www.youtube.com/watch?v=Rif-RTvmmss");
	r.add(m);
	try {
		MediaItem retrievedSong = r.find( m.getTitle(), m.getArtist());
	}
	catch(std::exception){
		assert(false);
	}

	MediaItem m2("Cruel Summer", "Taylor Swift", "jsjsjsjs");
	try {
		MediaItem retrievedSong = r.find( m2.getTitle(), m2.getArtist());
		assert(false);
	}
	catch (std::exception &e) {
		std::cout << "Exception thrown" << e.what();
	}
	//assert(r.getSongs().at(0) == m);
}

void RepoTester::testRemove()
{
}

void RepoTester::testSave()
{
}

void RepoTester::testLoad()
{
}
