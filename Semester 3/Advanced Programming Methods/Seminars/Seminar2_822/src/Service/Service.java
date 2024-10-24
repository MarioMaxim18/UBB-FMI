package Service;

import Repository.Repository;
import domain.Doctor;
import domain.Entity;

import java.util.ArrayList;

public class Service {
    private Repository repo;

    public Service(Repository repo) {
        this.repo = repo;
    }

    public void add(int id, String name, String specialty, double grade)
    {
        Doctor doc = new Doctor(id, name, specialty, grade);
        repo.add(doc);
    }

    public ArrayList<Doctor> getDoctors() {
        ArrayList<Entity> entities = repo.getAll();
        ArrayList<Doctor> doctors = new ArrayList<>();
        for (Entity entity : entities) {
            if (entity instanceof Doctor) {
                doctors.add((Doctor) entity);
            }
        }
        return doctors;
    }
}
