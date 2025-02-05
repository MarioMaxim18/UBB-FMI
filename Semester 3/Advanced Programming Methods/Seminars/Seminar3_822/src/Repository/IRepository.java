package Repository;

import domain.Entity;

public interface IRepository<ID, T extends Entity<ID>> {
    void add(ID id, T entity) throws RepositoryException;
    T findById(ID id);
    Iterable<T> getAll();
}
