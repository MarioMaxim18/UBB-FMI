package repository;

import domain.Dentist;
import domain.Identifiable;

import java.io.*;

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

    @Override
    public void deleteDentist(int id) throws RepositoryException {
        super.deleteDentist(id);
        writeToFile();
    }

    @Override
    public void modifyDentist(int id, T entity) throws RepositoryException {
        super.modifyDentist(id, entity);
        writeToFile();
    }
}