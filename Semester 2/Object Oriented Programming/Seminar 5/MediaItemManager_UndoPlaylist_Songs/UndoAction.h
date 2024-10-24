#pragma once
#include "repo.h"
class UndoAction {
public:
	virtual void executeUndo() = 0;
	//This is what we were missing during the seminar in terms of memory management
	//destructor needs to be virtual to ensure correct destruction
	// in the case of derived class objects
	//try it without „virtual” and with only derived class destructors present
	virtual ~UndoAction() {
		std::cout << "UndoAction destructor called.\n" << std::endl;
	}
};

class UndoAdd : public UndoAction {
private:
	Repository& repo;
	MediaItem item;
public:
	UndoAdd(Repository& _repo, const MediaItem& _item) : UndoAction{}, repo{ _repo }, item{ _item } {};
	void executeUndo() override;
	~UndoAdd() {
		std::cout << "UndoAdd destructor called.\n" << std::endl;
	}
};

class UndoDelete : public UndoAction {
private:
	Repository& repo;
	MediaItem item;
public:
	UndoDelete(Repository& _repo, const MediaItem& _item) : UndoAction{}, repo{ _repo }, item{ _item } {};
	void executeUndo() override;
	~UndoDelete() {
		std::cout << "UndoDelete destructor called.\n" << std::endl;
	}
};