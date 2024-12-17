package repository;

import domain.Appointment;
import domain.Dentist;
import domain.Identifiable;
import exceptions.RepoException;

import java.util.*;

public class MemoryRepository<T extends Identifiable> implements IRepository<Integer, T> {
    protected Map<Integer, T> dentists = new HashMap<>();
    protected Map<Integer, T> appointments = new HashMap<>();

    @Override
    public void addDentist(int id, T entity) {
        dentists.put(id, entity);
    }

    @Override
    public void deleteDentist(int id) {
        dentists.remove(id);
    }

    @Override
    public void modifyDentist(int id, T entity) {
        dentists.put(id, entity);
    }

    @Override
    public T findByIdDentist(int id) {
        return dentists.get(id);
    }

    @Override
    public Iterable<T> getAllDentists() {
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