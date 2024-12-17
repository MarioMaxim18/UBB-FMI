package repository;

import domain.Dentist;
import domain.Identifiable;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class MemoryRepository<T extends Identifiable> implements IRepository<Integer, T> {
    protected Map<Integer, T> dentists = new HashMap<>();
    protected Map<Integer, T> appointments = new HashMap<>();

    @Override
    public void addDentist(int id, T entity) throws RepositoryException {
        if (dentists.containsKey(id)) {
            throw new RepositoryException("A dentist with id " + id + " already exists.");
        }
        dentists.put(id, entity);
    }

    public void deleteDentist(int id) throws RepositoryException {
        if (!dentists.containsKey(id)) {
            throw new RepositoryException("Dentist with id " + id + " does not exist.");
        }
        dentists.remove(id);
    }

    @Override
    public void modifyDentist(int id, T entity) throws RepositoryException {
        if (!dentists.containsKey(id)) {
            throw new RepositoryException("Dentist with id " + id + " does not exist.");
        }
        dentists.put(id, entity);
    }

    @Override
    public T findByIdDentist(int id) throws RepositoryException {
        T dentist = dentists.get(id);
        if (dentist == null) {
            throw new RepositoryException("Dentist with id " + id + " not found.");
        }
        return dentist;
    }

    @Override
    public Iterable<T> getAllDentists()  {
        return dentists.values();
    }

    @Override
    public void addAppointment(int id, T entity) {
        appointments.put(id, entity);
    }

    @Override
    public void deleteAppointment(int id) {
        appointments.remove(id);
    }

    @Override
    public void modifyAppointment(int id, T entity) {
        appointments.put(id, entity);
    }

    @Override
    public T findByIdAppointment(int id) {
        return appointments.get(id);
    }

    @Override
    public Iterable<T> getAllAppointments() {
        return appointments.values();
    }

    @Override
    public int generateUniqueIDforAppointment() {
        Random randomID = new Random();
        boolean isUnique = false;
        int uniqueAppointmentId = 0;
        while (!isUnique) {
            isUnique = true;
            uniqueAppointmentId = randomID.nextInt(100);
            for (Identifiable appointment : appointments.values()) {
                if (appointment.getId() == uniqueAppointmentId) {
                    isUnique = false;
                    break;
                }
            }
        }
        return uniqueAppointmentId;
    }

    @Override
    public int generateUniqueIDforDentist() {
        Random randomID = new Random();
        boolean isUnique = false;
        int uniqueDentistId = 0;
        while (!isUnique) {
            isUnique = true;
            uniqueDentistId = randomID.nextInt(100);
            for (Identifiable dentist : dentists.values()) {
                if (dentist.getId() == uniqueDentistId) {
                    isUnique = false;
                    break;
                }
            }
        }
        return uniqueDentistId;
    }
}