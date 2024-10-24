#include "UndoAction.h"

void UndoAdd::executeUndo() {
	repo.deleteItem(*item);
}

void UndoDelete::executeUndo() {
	repo.store(item);
}
