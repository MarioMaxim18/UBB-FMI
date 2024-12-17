package repository;

import domain.Identifiable;

public interface IRepository<Integer, T extends Identifiable> {
    void addDentist(int id, T entity) throws RepositoryException;
    void deleteDentist(int id) throws RepositoryException;
    void modifyDentist(int id, T entity) throws RepositoryException;
    T findByIdDentist(int id) throws RepositoryException;
    Iterable<T> getAllDentists();

    void addAppointment(int id, T entity);
    void deleteAppointment(int id);
    void modifyAppointment(int id, T entity);
    T findByIdAppointment(int id);
    Iterable<T> getAllAppointments();

    int generateUniqueIDforAppointment();
    int generateUniqueIDforDentist();
}