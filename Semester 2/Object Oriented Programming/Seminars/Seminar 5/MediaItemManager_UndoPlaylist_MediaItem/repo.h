#pragma once
#include <vector>
#include "items.h"
#include <algorithm>
using std::vector;

class Repository {
private:
	string filename;


	vector<std::shared_ptr<MediaItem>> items;

	void loadData();
	void saveData();
	bool exists(const std::shared_ptr<MediaItem> item) const;
public:
	Repository(string filename = "data.txt") : filename{ filename } {
		this->loadData();
	};

	Repository(const Repository& repo) = delete;
	Repository& operator=(const Repository&) = delete;

	//add a media item
	void store(std::shared_ptr<MediaItem> item);
	/// <summary>
	/// Finds the MediaItem with specified title and artist
	/// </summary>
	/// <param name="title">The title we are searching by</param>
	/// <param name="artist">The artist we are searching by</param>
	/// <returns></returns>
	const std::shared_ptr<MediaItem> find(const string& title, const string& artist) const;
	
	/// <summary>
	/// Deletes the given item from the repository
	/// </summary>
	/// <param name="item">The item to be deleted</param>
	void deleteItem(const MediaItem& item);
	
	/// <summary>
	/// Gets all media items
	/// </summary>
	/// <returns></returns>
	const vector<std::shared_ptr<MediaItem>>& getAllSongs() { return this->items; };

	~Repository();
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


