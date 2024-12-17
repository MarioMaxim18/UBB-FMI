package service;

import domain.Appointment;
import domain.Dentist;
import domain.Identifiable;
import exceptions.RepoException;
import filter.*;
import repository.FilteredRepository;
import repository.IRepository;

import java.util.List;

public class Service {
    protected IRepository<Integer, Identifiable> repo;
    private FilteredRepository<Appointment> filteredAppointments;
    private FilteredRepository<Dentist> filteredDentists;

    public Service(IRepository<Integer, Identifiable> repo) {
        this.repo = repo;
    }

    public void setFilterAppointments(AbstractFilter<Appointment> filter) {
            filteredAppointments = new FilteredRepository<>(filter);
            for (Identifiable appointment : repo.getAllAppointments()) {
                filteredAppointments.addAppointment(appointment.getId(), (Appointment) appointment);
            }
    }

    public void setFilterDentists(AbstractFilter<Dentist> filter) {
            filteredDentists = new FilteredRepository<>(filter);
            for (Identifiable dentist : repo.getAllDentists()) {
                filteredDentists.addDentist(dentist.getId(), (Dentist) dentist);
            }
    }

    public List<Appointment> getFilteredAppointments() {
        return (List<Appointment>) filteredAppointments.getAllAppointments();
    }

    public List<Dentist> getFilteredDentists() {
        return (List<Dentist>) filteredDentists.getAllDentists();
    }

    public void addAppointment(Dentist dentist, int id, int time) {
        repo.addAppointment(id, new Appointment(dentist, id, time));
    }

    public void removeAppointment(int id) {
        repo.deleteAppointment(id);
    }

    public void updateAppointment(int id, int time) {
        repo.modifyAppointment(id, new Appointment(getAppointment(id).getDentist(), id, time));
    }

    public Appointment getAppointment(int id) {
        return (Appointment) repo.findByIdAppointment(id);
    }

    public int generateUniqueIDforAppointment() {
        return repo.generateUniqueIDforAppointment();
    }

    public int generateUniqueIDforDentist() {
        return repo.generateUniqueIDforDentist();
    }

    public void addDentist(int id, String name, String specialty, double grade) {
        repo.addDentist(id, new Dentist(id, name, specialty, grade));
    }

    public void deleteDentist(int id) {
        repo.deleteDentist(id);
    }

    public void updateDentist(int id, String name, String specialty, double grade) {
        repo.modifyDentist(id, new Dentist(id, name, specialty, grade));
    }

    public Dentist getDentist(int id) {
        return (Dentist) repo.findByIdDentist(id);
    }

    public Iterable<Identifiable> getAllDentists() throws RepoException {
        return repo.getAllDentists();
    }

    public List<Appointment> reports(Dentist dentist) {
        setFilterAppointments(new FilterAppointmentByDentist(dentist));
        return getFilteredAppointments();
    }

    public List<Appointment> filterAppointmentsByTime(int time) {
        setFilterAppointments(new FilterAppointmentByTime(time));
        return getFilteredAppointments();
    }

    public List<Dentist> filterDentistsBySpecialty(String specialty) {
        setFilterDentists(new FilterDentistBySpecialty(specialty));
        return getFilteredDentists();
    }

    public List<Dentist> filterDentistsByGrade(double grade) {
        setFilterDentists(new FilterDentistByGrade(grade));
        return getFilteredDentists();
    }
}
