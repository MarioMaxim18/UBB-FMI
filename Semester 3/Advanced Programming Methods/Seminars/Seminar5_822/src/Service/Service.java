package Service;

import Repository.IRepository;
import Repository.RepositoryException;
import domain.Appointment;
import domain.Doctor;
import domain.Patient;

import java.util.List;

import java.util.ArrayList;

public class Service {
    private IRepository<Integer, Doctor> doctorsRepo;
    private IRepository<Integer, Patient> patientsRepo;
    private IRepository<Integer, Appointment> appointmentsRepo;

    public Service(IRepository<Integer, Doctor> doctorsRepo, IRepository<Integer, Patient> patientsRepo, IRepository<Integer, Appointment> appointmentsRepo) {

        this.doctorsRepo = doctorsRepo;
        this.patientsRepo = patientsRepo;
        this.appointmentsRepo = appointmentsRepo;
    }

    public void add(int id, String name, String specialty, double grade) throws RepositoryException
    {
        Doctor doc = new Doctor(id, name, specialty, grade);
        doctorsRepo.add(id, doc);
    }

    public Iterable<Doctor> getDoctors() {
        return doctorsRepo.getAll();
    }

    public Iterable<Patient> getPatients() {
        return patientsRepo.getAll();
    }

    public Iterable<Appointment> getAppointments() {
        return appointmentsRepo.getAll();
    }

    public Iterable<Doctor> getSortedDoctors() {
        List<Doctor> doctors = new ArrayList<>();
        for (Doctor d: doctorsRepo.getAll())
            doctors.add(d);

        List<Doctor> sortedDoctors = doctors.stream()
                .sorted((d1, d2) -> d1.getName().compareTo(d2.getName()))
                .toList();
        return sortedDoctors;
    }
    public List<Patient> allPatientsAppointmentAtDoctor(String doctorName){
        List<Appointment> appointments= new ArrayList<>();
        for (Appointment a: appointmentsRepo.getAll())
            appointments.add(a);

        List<Patient> result = appointments.stream()
                .filter(appointment -> appointment.getDoctor().getName().equals(doctorName))
                .map(appointment -> appointment.getPatient())
                .sorted((p1, p2) -> p1.getName().compareTo(p2.getName()))
                .toList();
        return result;
    }
}
