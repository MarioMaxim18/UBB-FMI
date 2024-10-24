package UI;

import domain.Appointment;
import domain.Dentist;
import service.Service;
import java.util.Scanner;

public class UI {
    protected Service service;
    protected boolean start = true;

    public UI (Service service) {
        this.service = service;
    }
    public void displayMenu() {
        System.out.println("1. Add appointment");
        System.out.println("2. View appointment");
        System.out.println("3. Update appointment");
        System.out.println("4. Cancel appointment");
        System.out.println("5. View report");
        System.out.println("0. Exit");
    }

    public void run() {
        populateList();
        while(start) {
            displayMenu();
            System.out.println("Option:");
            Scanner scanner = new Scanner(System.in);
            int option = scanner.nextInt();
            if (option == 1) {
                System.out.println("Enter the id:");
                int id = scanner.nextInt();
                if (service.uniqueIDCheck(id)) {
                    System.out.println("The id already exists");
                } else {
                    System.out.println("Enter the time:");
                    int time = scanner.nextInt();
                    System.out.println("Enter dentist's name: ");
                    scanner.nextLine();
                    String name = scanner.nextLine();
                    Dentist dentist = new Dentist(name);
                    service.addAppointment(dentist, id, time);
                }
            } else if (option == 2) {
                System.out.println("Enter the id:");
                int id = scanner.nextInt();
                Appointment appointment = service.getAppointment(id);
                if (appointment == null) {
                    System.out.println("The id does not exist");
                } else {
                    System.out.println(appointment.toString());
                }
            } else if (option == 3) {
                System.out.println("Enter the id:");
                int id = scanner.nextInt();
                if (!service.uniqueIDCheck(id)) {
                    System.out.println("The id does not exist");
                } else {
                    System.out.println("Enter the new time");
                    int time = scanner.nextInt();
                    service.updateAppointment(id, time);
                }
            } else if (option == 4) {
                System.out.println("Enter the id:");
                int id = scanner.nextInt();
                if (!service.uniqueIDCheck(id)) {
                    System.out.println("The id does not exist");
                } else {
                    service.removeAppointment(id);
                }
            } else if (option == 5) {
                System.out.println("Enter the dentist's name:");
                scanner.nextLine();
                String name = scanner.nextLine();
                Dentist dentist = new Dentist(name);
                Appointment[] report = service.reports(dentist);
                int reportSize = service.getReportSize();
                if (reportSize == 0) {
                    System.out.println("The dentist does not have any appointments");
                } else {
                    for (int i = 0; i < reportSize; i++) {
                        System.out.println(report[i].toString());
                    }
                }
            }
            else if (option == 0) {
                System.out.println("Now exiting...");
                start = false;
            } else {
                System.out.println("Invalid option");
            }
        }
    }

    void populateList() {
        service.addAppointment(new Dentist("Mario"), 1, 10);
        service.addAppointment(new Dentist("Andrei"), 2, 11);
        service.addAppointment(new Dentist("Andrei"), 3, 8);
        service.addAppointment(new Dentist("Matei"), 4, 12);
        service.addAppointment(new Dentist("Matei"), 5, 9);
        service.addAppointment(new Dentist("Matei"), 6, 14);
    }
}
