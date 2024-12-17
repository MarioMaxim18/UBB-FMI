package repository;

import domain.Dentist;
import domain.Identifiable;
import repository.IRepository;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class FakeRepo implements IRepository<Integer, Identifiable> {
    @Override
    public void addDentist(int id, Identifiable entity) throws RepositoryException {

    }

    @Override
    public void deleteDentist(int id) throws RepositoryException {

    }

    @Override
    public void modifyDentist(int id, Identifiable entity) throws RepositoryException {

    }

    @Override
    public Identifiable findByIdDentist(int id) throws RepositoryException {
        Dentist dentist = new Dentist(id, "Matei", "Orthodontist", 4.5);
        return dentist;
    }

    @Override
    public Iterable<Identifiable> getAllDentists() {
        Dentist firstDentist = new Dentist(1, "Matei", "Orthodontist", 4.5);
        Dentist secondDentist = new Dentist(2, "Mario", "General Dentist", 3.8);
        ArrayList<Identifiable> data = new ArrayList<>();
        data.add(firstDentist);
        data.add(secondDentist);
        return data;
    }

    @Override
    public void addAppointment(int id, Identifiable entity) {
    }

    @Override
    public void deleteAppointment(int id)  {

    }

    @Override
    public void modifyAppointment(int id, Identifiable entity) {
    }

    @Override
    public Identifiable findByIdAppointment(int id) {
        return null;
    }

    @Override
    public Iterable<Identifiable> getAllAppointments() {
        return null;
    }

    @Override
    public int generateUniqueIDforAppointment() {
        return 0;
    }

    @Override
    public int generateUniqueIDforDentist() {
        return 0;
    }
}