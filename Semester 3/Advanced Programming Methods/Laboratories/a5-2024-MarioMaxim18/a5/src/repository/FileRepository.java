package repository;

import domain.Identifiable;

public abstract class FileRepository< T extends Identifiable> extends MemoryRepository<T> {
    protected String filename;

    public FileRepository(String filename) throws RepositoryException {
        this.filename = filename;
        this.readFromFile();
    }

    protected abstract void readFromFile() throws RepositoryException;
    protected abstract void writeToFile();

    @Override
    public void addDentist(int id, T entity) throws RepositoryException {
        super.addDentist(id, entity);
        writeToFile();
    }
}