package action;

import repository.RepositoryException;

public interface IAction {
    void executeUndo() throws RepositoryException;
    void executeRedo() throws RepositoryException;
}
