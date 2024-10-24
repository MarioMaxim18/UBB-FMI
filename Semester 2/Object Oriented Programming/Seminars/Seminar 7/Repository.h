#include<vector>
#include"MediaItem.h"
#include<string>
#include<stdexcept>

#pragma once
class Repository
{
protected:
	std::vector<MediaItem> songs;
public:
	std::vector<MediaItem>& getSongs();
	Repository() = default;
	Repository(const Repository&) = delete; //delete the copy and assingment operators
	Repository& operator=(const Repository&) = delete;
	virtual void add(const MediaItem &newSong);
	virtual void remove(const MediaItem &song);
	const MediaItem &find(std::string title, std::string artist) const noexcept(false); // this function can throw exceptions
	virtual ~Repository()=default; //provide the default implementation
};

class FileRepository : public Repository {
private:
	std::string path;
	void save();
	void load();
public:

	void add(const MediaItem &newSong) override;// refrence to the media item object
	void remove(const MediaItem &song) override;

};

class RepoException : public std::exception {
private:
	std::string message;
public:
	RepoException(std::string msg) {
		message = msg;
	}
	const char* what() const noexcept override { // noexcept - it doesnt throw any exception
		return message.c_str();
	};
};

class RepoTester {
public:
	static void testAll() {
		testAdd();
		testFind();
		testRemove();
		testSave();
		testLoad();
	}
private:
	static void testAdd();
	static void testFind();
	static void testRemove();
	static void testSave();
	static void testLoad();
};


