package service;

import action.*;
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
    protected IRepository<Integer, Identifiable> AppointmentRepo;
    protected IRepository<Integer, Identifiable> DentistRepo;
    private FilteredRepository<Appointment> filteredAppointments;
    private FilteredRepository<Dentist> filteredDentists;
    protected UndoRedoService undoRedoService;

    public Service(IRepository<Integer, Identifiable> DentistRepo, IRepository<Integer, Identifiable> AppointmentRepo) {
        this.AppointmentRepo = AppointmentRepo;
        this.DentistRepo = DentistRepo;
        this.undoRedoService = new UndoRedoService();
    }

    public void setFilterAppointments(AbstractFilter<Appointment> filter) throws RepositoryException {
        filteredAppointments = new FilteredRepository<>(filter);
        for (Identifiable appointment : AppointmentRepo.getAllAppointments()) {
            filteredAppointments.addAppointment(appointment.getId(), (Appointment) appointment);
        }
    }

    public void setFilterDentists(AbstractFilter<Dentist> filter) throws RepositoryException {
        filteredDentists = new FilteredRepository<>(filter);
        for (Identifiable dentist : DentistRepo.getAllDentists()) {
            filteredDentists.addDentist(dentist.getId(), (Dentist) dentist);
        }
    }

    public List<Appointment> getFilteredAppointments() {
        return (List<Appointment>) filteredAppointments.getAllAppointments();
    }

    public List<Dentist> getFilteredDentists()  {
        return (List<Dentist>) filteredDentists.getAllDentists();
    }

    public void addAppointment(Dentist dentist, int id, int time) throws RepositoryException {
        undoRedoService.executeAction(new AddAppointmentAction(AppointmentRepo, new Appointment(dentist, id, time)));
    }

    public void removeAppointment(int id) throws RepositoryException {
        undoRedoService.executeAction(new DeleteAppointmentAction(AppointmentRepo, (Appointment) AppointmentRepo.findByIdAppointment(id)));
    }

    public void updateAppointment(int id, int time) throws RepositoryException {
        Appointment oldAppointment = (Appointment) AppointmentRepo.findByIdAppointment(id);
        Appointment updatedAppointment = new Appointment(oldAppointment.getDentist(), id, time);
        undoRedoService.executeAction(new UpdateAppointmentAction(AppointmentRepo, oldAppointment, updatedAppointment));
    }

    public Appointment getAppointment(int id) throws RepositoryException {
        return (Appointment) AppointmentRepo.findByIdAppointment(id);
    }

    public Iterable<Identifiable> getAllAppointments() {
        return AppointmentRepo.getAllAppointments();
    }

    public int generateUniqueIDforAppointment() {
        return AppointmentRepo.generateUniqueIDforAppointment();
    }

    public int generateUniqueIDforDentist() {
        return DentistRepo.generateUniqueIDforDentist();
    }

    public void addDentist(int id, String name, String specialty, double grade) throws RepositoryException{
        undoRedoService.executeAction(new AddDentistAction(DentistRepo, new Dentist(id, name, specialty, grade)));
    }

    public void deleteDentist(int id) throws RepositoryException {
        undoRedoService.executeAction(new DeleteDentistAction(DentistRepo, (Dentist) DentistRepo.findByIdDentist(id)));
    }

    public void updateDentist(int id, String name, String specialty, double grade) throws RepositoryException {
        Dentist oldDentist = (Dentist) DentistRepo.findByIdDentist(id);
        Dentist updatedDentist = new Dentist(id, name, specialty, grade);
        undoRedoService.executeAction(new UpdateDentistAction(DentistRepo, oldDentist, updatedDentist));
    }

    public Dentist getDentist(int id) throws RepositoryException {
        return (Dentist) DentistRepo.findByIdDentist(id);
    }

    public Iterable<Identifiable> getAllDentists() throws RepositoryException {
        return DentistRepo.getAllDentists();
    }

    public List<Appointment> reports(Dentist dentist) throws RepositoryException {
        setFilterAppointments(new FilterAppointmentByDentist(dentist));
        return getFilteredAppointments();
    }

    public List<Appointment> filterAppointmentsByTime(int time) throws RepositoryException {
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
        for (Identifiable d: DentistRepo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> d1.getName().compareTo(d2.getName()))
                .toList();
        return sortedDentists;
    }

    public List<Dentist> getSortedDentistsByGrade() {
        List<Dentist> dentists = new ArrayList<>();
        for (Identifiable d: DentistRepo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> Double.compare(d1.getGrade(), d2.getGrade()))
                .toList();
        return sortedDentists;
    }

    public List<Dentist> getSortedDentistsBySpecialty() {
        List<Dentist> dentists = new ArrayList<>();
        for (Identifiable d: DentistRepo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> d1.getSpecialty().compareTo(d2.getSpecialty()))
                .toList();
        return sortedDentists;
    }

    public List<Dentist> getSortedDentistsByID() {
        List<Dentist> dentists = new ArrayList<>();
        for (Identifiable d: DentistRepo.getAllDentists())
            dentists.add((Dentist) d);
        List<Dentist> sortedDentists = dentists.stream()
                .sorted((d1, d2) -> d1.getId() - d2.getId())
                .toList();
        return sortedDentists;
    }

    public List<Appointment> getSortedAppointmentsByTime() {
        List<Appointment> appointments = new ArrayList<>();
        for (Identifiable a: AppointmentRepo.getAllAppointments())
            appointments.add((Appointment) a);
        List<Appointment> sortedAppointments = appointments.stream()
                .sorted((a1, a2) -> a1.getTime() - a2.getTime())
                .toList();
        return sortedAppointments;
    }

    public void undo() throws RepositoryException {
        undoRedoService.undo();
    }

    public void redo() throws RepositoryException {
        undoRedoService.redo();
    }
}
