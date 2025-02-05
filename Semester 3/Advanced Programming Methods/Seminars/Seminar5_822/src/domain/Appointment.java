package domain;

import java.time.LocalDateTime;

public class Appointment extends Entity<Integer>{
    private Doctor doctor;
    private Patient patient;
    private LocalDateTime dateTime;

    public Appointment(Integer id, Doctor doctor, Patient patient, LocalDateTime dateTime) {
        super(id);
        this.doctor = doctor;
        this.patient = patient;
        this.dateTime = dateTime;
    }

    public Doctor getDoctor() {
        return doctor;
    }

    public void setDoctor(Doctor doctor) {
        this.doctor = doctor;
    }

    public Patient getPatient() {
        return patient;
    }

    public void setPatient(Patient patient) {
        this.patient = patient;
    }

    public LocalDateTime getDateTime() {
        return dateTime;
    }

    public void setDateTime(LocalDateTime dateTime) {
        this.dateTime = dateTime;
    }

    @Override
    public String toString() {
        return "Appointment{" +
                "doctor=" + doctor +
                ", patient=" + patient +
                ", dateTime=" + dateTime +
                '}';
    }
}
