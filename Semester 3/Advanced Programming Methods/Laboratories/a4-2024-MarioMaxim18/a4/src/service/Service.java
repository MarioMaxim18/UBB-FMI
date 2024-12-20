package service;

import domain.Appointment;
import domain.Dentist;
import domain.Identifiable;
import exceptions.RepoException;
import filter.*;
import repository.FilteredRepository;
import repository.IRepository;
import repository.RepositoryException;

import java.util.ArrayList;
import java.util.List;

public class Service<T extends Identifiable> {
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

    public void setFilterDentists(AbstractFilter<Dentist> filter) throws RepositoryException {
            filteredDentists = new FilteredRepository<>(filter);
            for (Identifiable dentist : repo.getAllDentists()) {
                filteredDentists.addDentist(dentist.getId(), (Dentist) dentist);
            }
    }

    public List<Appointment> getFilteredAppointments() {
        return (List<Appointment>) filteredAppointments.getAllAppointments();
    }

    public List<Dentist> getFilteredDentists()  {
        return (List<Dentist>) filteredDentists.getAllDentists();
    }

    public void addAppointment(Dentist dentist, int id, int time)  {
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

    public void addDentist(int id, String name, String specialty, double grade) throws RepositoryException{
        repo.addDentist(id, new Dentist(id, name, specialty, grade));
    }

    public void deleteDentist(int id) throws RepositoryException {
        repo.deleteDentist(id);
    }

    public void updateDentist(int id, String name, String specialty, double grade) throws RepositoryException{
        repo.modifyDentist(id, new Dentist(id, name, specialty, grade));
    }

    public Dentist getDentist(int id) throws RepositoryException {
        return (Dentist) repo.findByIdDentist(id);
    }

    public Iterable<Identifiable> getAllDentists() throws RepositoryException {
        return repo.getAllDentists();
    }

    public List<Appointment> reports(Dentist dentist)  {
        setFilterAppointments(new FilterAppointmentByDentist(dentist));
        return getFilteredAppointments();
    }

    public List<Appointment> filterAppointmentsByTime(int time)  {
        setFilterAppointments(new FilterAppointmentByTime(time));
        return getFilteredAppointments();
    }

    public List<Dentist> filterDentistsBySpecialty(String specialty) throws RepositoryException {
        setFilterDentists(new FilterDentistBySpecialty(specialty));
        return getFilteredDentists();
    }

    public List<Dentist> filterDentistsByGrade(double grade) throws RepositoryException {
        setFilterDentists(new FilterDentistByGrade(grade));
        return getFilteredDentists();
    }

    public List<Dentist> getSortedDentistsByName() {
        List<Dentist> dentists = new ArrayList<>();
        for (Identifiable d: repo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> d1.getName().compareTo(d2.getName()))
                .toList();
        return sortedDentists;
    }

    public List<Dentist> getSortedDentistsByGrade() {
        List<Dentist> dentists = new ArrayList<>();
        for (Identifiable d: repo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> Double.compare(d1.getGrade(), d2.getGrade()))
                .toList();
        return sortedDentists;
    }

    public List<Dentist> getSortedDentistsBySpecialty() {
        List<Dentist> dentists = new ArrayList<>();
        for (Identifiable d: repo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> d1.getSpecialty().compareTo(d2.getSpecialty()))
                .toList();
        return sortedDentists;
    }

    public List<Dentist> getSortedDentistsByID() {
        List<Dentist> dentists = new ArrayList<>();
        for (Identifiable d: repo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> d1.getId() - d2.getId())
                .toList();
        return sortedDentists;
    }

    public List<Appointment> getSortedAppointmentsByTime() {
        List<Appointment> appointments = new ArrayList<>();
        for (Identifiable a: repo.getAllAppointments())
            appointments.add((Appointment) a);
        List<Appointment> sortedAppointments = appointments.stream()
                .sorted((a1, a2) -> a1.getTime() - a2.getTime())
                .toList();
        return sortedAppointments;
    }
}
