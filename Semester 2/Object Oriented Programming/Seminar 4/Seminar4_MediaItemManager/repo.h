#pragma once
#include <vector>
#include "items.h"
using std::vector;

class Repository {
private:
	string filename;
	vector<MediaItem*> items;
	void loadData();
	void saveData();
	bool exists(const MediaItem* item) const;
public:
	Repository(string filename = "data.txt") : filename{ filename } {
		this->loadData();
	};
	Repository(const Repository& repo) = delete;
	void store(MediaItem* item);
	const MediaItem* find(const string& title, const string& artist) const;
	const vector<MediaItem*>& getAllSongs() { return this->items; };
};

class RepoException {
private:
	string errorMsg;
public:
	RepoException(const string& errorMsg) :errorMsg{ errorMsg } { };
	string getErrorMsg() const {
		return this->errorMsg;
	};
	friend ostream& operator<<(ostream& stream, const RepoException& exception);
};