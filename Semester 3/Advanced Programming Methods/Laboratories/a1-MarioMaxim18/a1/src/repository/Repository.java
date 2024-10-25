package repository;

import domain.Appointment;
import domain.Dentist;

import java.util.Objects;

public class Repository {
    private static final int INITIAL_CAPACITY = 10;
    protected Appointment[] listWithAppointments;
    protected int length;
    protected Dentist[] listWithDentists;
    protected int dentistCount;
    protected int reportSize;

    public Repository() {
        this.listWithAppointments = new Appointment[INITIAL_CAPACITY];
        length = 0;
        this.listWithDentists = new Dentist[INITIAL_CAPACITY];
        dentistCount = 0;
    }

    public boolean findDentist(Dentist dentist) {
        for (int i = 0; i < dentistCount; i++) {
            if (dentist.getName().equals(listWithDentists[i].getName())) {
                return true;
            }
        }
        return false;
    }

    public void addAppointment(Appointment appointment) {
        listWithAppointments[length++] = appointment;
        if (!findDentist(appointment.getDentist())) {
            listWithDentists[dentistCount++] = appointment.getDentist();
        }
    }

    public void removeAppointment(int id) {
        Appointment[] newAppointments = new Appointment[INITIAL_CAPACITY];
        int newLength = 0;
        for (int i = 0; i < length; i++) {
            if(listWithAppointments[i].getId() != id) {
                newAppointments[newLength++] = listWithAppointments[i];
            }
        }
        this.listWithAppointments = newAppointments;
    }

    public void updateAppointment(int id, int time) {
        for (int i = 0; i < length; i++) {
            if (listWithAppointments[i].getId() == id) {
                listWithAppointments[i].setTime(time);
            }
        }
    }

    public Appointment getAppointment(int id) {
        for (int i = 0; i < length; i++) {
            if (listWithAppointments[i].getId() == id) {
                return listWithAppointments[i];
            }
        }
        return null;
    }

    public Appointment[] reports(Dentist dentist) {
        reportSize = 0;
        Appointment[] reportsForDentist = new Appointment[INITIAL_CAPACITY];
        for (int i = 0; i < length; i++) {
            if (Objects.equals(dentist.getName(), listWithAppointments[i].getDentist().getName())) {
                reportsForDentist[reportSize++] = listWithAppointments[i];
            }
        }
        return reportsForDentist;
    }

    public int getReportSize() {
        return reportSize;
    }

    public boolean uniqueIDCheck(int id) {
        for (int i = 0; i < length; i++) {
            if (listWithAppointments[i].getId() == id) {
                return true;
            }
        }
        return false;
    }
}