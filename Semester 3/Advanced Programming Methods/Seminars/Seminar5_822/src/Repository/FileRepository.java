package Repository;

import domain.Entity;

import java.io.FileNotFoundException;
import java.io.IOException;

public abstract class FileRepository<ID, T extends Entity<ID>> extends Repository<ID, T> {
    protected String filename;

    public FileRepository(String filename) throws RepositoryException {
        this.filename = filename;
        this.readFromFile();
    }

    protected abstract void readFromFile() throws RepositoryException;
    protected abstract void writeToFile();

    @Override
    public void add(ID id, T entity) throws RepositoryException
    {
        super.add(id, entity);
        writeToFile();
    }
}
