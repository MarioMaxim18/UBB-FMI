package main;

import Repository.*;
import Service.Service;
import domain.Appointment;
import domain.Doctor;
import domain.Patient;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.Properties;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void printElems(Repository<Integer, Doctor> r){
        for(Doctor doctor: r.getAll())
            System.out.println(doctor);
    }

    public static void main(String[] args) {
        IRepository<Integer, Doctor> doctorsRepository = null;
        IRepository<Integer, Patient> patientsRepository= new PatientsRepository();
        IRepository<Integer, Appointment> appointmentsRepository= new AppointmentsRepository();

        Patient patient1= new Patient(1,"Mihai","Cluj");
        Patient patient2= new Patient(2,"Ion","Bucuresti");

        try {
            patientsRepository.add(patient1.getID(), patient1);
            patientsRepository.add(patient2.getID(), patient2);
        }catch(RepositoryException e){
            System.out.println(e.getMessage());
        }
        // read the properties file
        FileReader fr = null;
        try {
            fr = new FileReader("settings.properties");
            Properties prop = new Properties();
            prop.load(fr);

            String repositoryType = (String) prop.get("repo_type");
            String repositoryPath = prop.getProperty("repo_path");

            if (repositoryType.equals("text"))
                doctorsRepository = new DoctorsTextFileRepository(repositoryPath);

            if (repositoryType.equals("binary"))
                doctorsRepository = new DoctorsBinaryFileRepository(repositoryPath);

            if (repositoryType.equals("DB"))
                doctorsRepository = new DoctorsDBRepository();

            if (repositoryType.equals("memory"))
                doctorsRepository = new DoctorsRepository();

//            for (Doctor d: doctorsRepository.getAll())
//                System.out.println(d);
            Appointment appointment1= new Appointment(1,doctorsRepository.findById(10),patient1, LocalDateTime.of(2024,11,27,12,30));
            Appointment appointment2= new Appointment(2,doctorsRepository.findById(22),patient1, LocalDateTime.of(2024,11,28,12,30));
            Appointment appointment3= new Appointment(3,doctorsRepository.findById(10),patient2, LocalDateTime.of(2024,12,28,12,30));
            Appointment appointment4= new Appointment(4,doctorsRepository.findById(88),patient2, LocalDateTime.of(2024,10,28,12,30));

            appointmentsRepository.add(appointment1.getID(),appointment1);
            appointmentsRepository.add(appointment2.getID(),appointment2);
            appointmentsRepository.add(appointment3.getID(),appointment3);
            appointmentsRepository.add(appointment4.getID(),appointment4);

            Service serv = new Service(doctorsRepository,patientsRepository,appointmentsRepository);
            UI ui = new UI(serv);
            ui.run();

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }
    }
}