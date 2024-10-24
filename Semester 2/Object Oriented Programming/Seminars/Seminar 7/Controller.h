#include"Repository.h"
#pragma once
#include<stack>
using std::stack;
#include<memory>
using std::unique_ptr;

class UndoAction {
public:
	virtual void executeUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd:public UndoAction {
private:
	MediaItem addedSong;
	Repository& r;
public:
	UndoAdd(MediaItem paddedSong, Repository& pr) :r{ pr } {
		addedSong = paddedSong;
	}
	void executeUndo() override {
		r.remove(addedSong);
	}
};
class UndoRemove :public UndoAction {
	MediaItem deletedSong;
	Repository& r;
public:
	UndoRemove(MediaItem pdeletedSong, Repository& pr) :r{ pr } {
		deletedSong = pdeletedSong;
	}
	void executeUndo() override {
		r.add(deletedSong);
	}
};
class UndoUpdate :public UndoAction {

};
class Controller
{
private:
	Repository& r;
	//stack<UndoAction*>;
	stack<unique_ptr<UndoAction>> UndoStack;
public:
    Controller(Repository& repo):r{repo}{}
	void add(string title, string artist, string path);
	void remove(string title, string artist);
//	const MediaItem& find(string title, string artist) const noexcept(false);
	void undo();
};

