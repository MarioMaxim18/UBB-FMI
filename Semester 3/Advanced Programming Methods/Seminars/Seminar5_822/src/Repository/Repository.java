package Repository;

import domain.Doctor;
import domain.Entity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class Repository<ID, T extends Entity<ID>> implements IRepository<ID, T> {

    protected HashMap<ID,T> entities= new HashMap<>();
    @Override
    public void add(ID id, T entity) throws RepositoryException{
        if(!entities.containsKey(id))
            entities.put(id,entity);
        else
            throw new RepositoryException("An object with id " + id + " already exists.");
    }

    @Override
    public T findById(ID id) {
        return entities.get(id);
    }

    @Override
    public Iterable<T> getAll() {
        return entities.values();
    }
}
