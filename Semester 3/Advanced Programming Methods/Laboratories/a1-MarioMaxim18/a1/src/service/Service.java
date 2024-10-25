package service;

import domain.Appointment;
import domain.Dentist;
import  repository.Repository;

public class Service {
    protected Repository repo;

    public Service(Repository repo) {
        this.repo = repo;
    }
    public void addAppointment(Dentist dentist, int id, int time) {
        repo.addAppointment(new Appointment(dentist, id, time));
    }

    public void removeAppointment(int id) {
        repo.removeAppointment(id);
    }

    public void updateAppointment(int  id, int time) {
       repo.updateAppointment(id, time);
    }

    public Appointment getAppointment(int id) {
        return repo.getAppointment(id);
    }

    public boolean findDentist(Dentist dentist) {
        return repo.findDentist(dentist);
    }

    public Appointment[] reports(Dentist dentist) {
        return repo.reports(dentist);
    }

    public int getReportSize() {
        return repo.getReportSize();
    }

    public boolean uniqueIDCheck(int id) {
        return repo.uniqueIDCheck(id);
    }
}
