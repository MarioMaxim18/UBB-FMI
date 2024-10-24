package Service;

import Repository.Repository;
import domain.Doctor;

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
        return repo.getAll();
    }
}
