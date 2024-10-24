package Repository;

import domain.Doctor;
import domain.Entity;

import java.util.ArrayList;
import java.util.Iterator;

public class Repository {
    protected ArrayList<Entity> entities = new ArrayList<>();

    public void add(Entity entity) {
        entities.add(entity);
    }

    public Iterator<Entity> iterator() {
        return entities.iterator();
    }

    public ArrayList<Entity> getAll() {
        return entities;
    }
}
