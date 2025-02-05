package main;

import Repository.*;
import Service.Service;
import domain.Patient;

import java.util.List;
import java.util.Scanner;

public class UI {
    private Service serv;

    public UI(Service serv) {
        this.serv = serv;
    }

    void printMenu() {
        System.out.println("1 - Add doctor.");
        System.out.println("2 - Print all doctors.");
        System.out.println("3 - Print all doctors, sorted by name.");
        System.out.println("4 - Print all patients.");
        System.out.println("5 - Print all appointments.");
        System.out.println("6 - Print all patients having appointments at doctor (given).");
        System.out.println("0 - Exit.");
    }

    void run() {
        while (true)
        {
            Scanner scanner = new Scanner(System.in);
            printMenu();
            System.out.println("Input an option: ");
            int option = scanner.nextInt();
            switch (option) {
                case 1:
                    System.out.println("Id: ");
                    int id = scanner.nextInt();
                    System.out.println("Name: ");
                    String name = scanner.next();
                    System.out.println("Specialty: ");
                    String specialty = scanner.next();
                    System.out.println("Grade: ");
                    double grade = scanner.nextDouble();
                    try {
                        serv.add(id, name, specialty, grade);
                    }
                    catch (RepositoryException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                case 2:
                    System.out.println(serv.getDoctors());
                    break;
                case 3:
                    System.out.println(serv.getSortedDoctors());
                    break;
                case 4:
                    System.out.println(serv.getPatients());
                    break;
                case 5:
                    System.out.println(serv.getAppointments());
                    break;
                case 6:
                    String doctorName = "Michael";
                    List<Patient> patientsResult = serv.allPatientsAppointmentAtDoctor(doctorName);
                    for(Patient p:patientsResult)
                        System.out.println(p.toString());
                    break;
                case 0:
                        return;
            }
        }
    }

}
