package repository;

import domain.Appointment;
import domain.Dentist;
import domain.Identifiable;

import java.util.List;

public interface IRepository<Integer, T extends Identifiable> {
    void addDentist(int id, T entity);
    void deleteDentist(int id);
    void modifyDentist(int id, T entity);
    T findByIdDentist(int id);
    Iterable<T> getAllDentists();

    void addAppointment(int id, T entity);
    void deleteAppointment(int id);
    void modifyAppointment(int id, T entity);
    T findByIdAppointment(int id);
    Iterable<T> getAllAppointments();
    int generateUniqueIDforAppointment();
    int generateUniqueIDforDentist();
}