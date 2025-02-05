package Service;

import Repository.DoctorsRepository;
import Repository.IRepository;
import Repository.RepositoryException;
import domain.Doctor;
import domain.Entity;

import java.util.ArrayList;

public class Service {
    private IRepository<Integer, Doctor> repo;

    public Service(IRepository<Integer, Doctor> repo) {
        this.repo = repo;
    }

    public void add(int id, String name, String specialty, double grade) throws RepositoryException
    {
        Doctor doc = new Doctor(id, name, specialty, grade);
        repo.add(id, doc);
    }

    public Iterable<Doctor> getDoctors() {
        return repo.getAll();
    }
}
