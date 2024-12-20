package service;

import action.IAction;
import repository.RepositoryException;

import java.util.Stack;

public class UndoRedoService {
    private final Stack<IAction> undoStack = new Stack<>();
    private final Stack<IAction> redoStack = new Stack<>();

    public void executeAction(IAction action) throws RepositoryException {
        action.executeRedo();
        undoStack.push(action);
        redoStack.clear();
    }

    public void undo() throws RepositoryException {
        if (!undoStack.isEmpty()) {
            IAction action = undoStack.pop();
            action.executeUndo();
            redoStack.push(action);
        }
    }

    public void redo() throws RepositoryException {
        if (!redoStack.isEmpty()) {
            IAction action = redoStack.pop();
            action.executeRedo();
            undoStack.push(action);
        }
    }
}