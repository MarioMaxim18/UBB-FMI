package UI;

import domain.Appointment;
import domain.Dentist;
import service.Service;
import java.util.Scanner;

public class UI {
    private static final int EXIT_OPTION = 0;
    private static final int ADD_APPOINTMENT_OPTION = 1;
    private static final int VIEW_APPOINTMENT_OPTION = 2;
    private static final int UPDATE_APPOINTMENT_OPTION = 3;
    private static final int CANCEL_APPOINTMENT_OPTION = 4;
    private static final int VIEW_REPORT_OPTION = 5;

    protected Service service;
    protected boolean CheckIfUserWantToExitFromMenu = true;

    public UI(Service service) {
        this.service = service;
    }

    public void displayMenu() {
        System.out.println(ADD_APPOINTMENT_OPTION + ". Add appointment");
        System.out.println(VIEW_APPOINTMENT_OPTION + ". View appointment");
        System.out.println(UPDATE_APPOINTMENT_OPTION + ". Update appointment");
        System.out.println(CANCEL_APPOINTMENT_OPTION + ". Cancel appointment");
        System.out.println(VIEW_REPORT_OPTION + ". View report");
        System.out.println(EXIT_OPTION + ". Exit");
    }

    public void run() {
        populateList();
        while(CheckIfUserWantToExitFromMenu) {
            displayMenu();
            System.out.println("Option:");
            Scanner scanner = new Scanner(System.in);
            int userChoice = scanner.nextInt();
            if (userChoice == ADD_APPOINTMENT_OPTION) {
                System.out.println("Enter the id:");
                int appointmentID = scanner.nextInt();
                if (service.uniqueIDCheck(appointmentID)) {
                    System.out.println("The id already exists");
                } else {
                    System.out.println("Enter the time:");
                    int time = scanner.nextInt();
                    System.out.println("Enter dentist's name: ");
                    scanner.nextLine();
                    String dentistName = scanner.nextLine();
                    Dentist dentist = new Dentist(dentistName );
                    service.addAppointment(dentist, appointmentID, time);
                }
            } else if (userChoice == VIEW_APPOINTMENT_OPTION) {
                System.out.println("Enter the id:");
                int appointmentID = scanner.nextInt();
                Appointment appointment = service.getAppointment(appointmentID);
                if (appointment == null) {
                    System.out.println("The id does not exist");
                } else {
                    System.out.println(appointment);
                }
            } else if (userChoice == UPDATE_APPOINTMENT_OPTION) {
                System.out.println("Enter the id:");
                int appointmentID = scanner.nextInt();
                if (!service.uniqueIDCheck(appointmentID)) {
                    System.out.println("The id does not exist");
                } else {
                    System.out.println("Enter the new time");
                    int time = scanner.nextInt();
                    service.updateAppointment(appointmentID, time);
                }
            } else if (userChoice == CANCEL_APPOINTMENT_OPTION) {
                System.out.println("Enter the id:");
                int appointmentID = scanner.nextInt();
                if (!service.uniqueIDCheck(appointmentID)) {
                    System.out.println("The id does not exist");
                } else {
                    service.removeAppointment(appointmentID);
                }
            } else if (userChoice == VIEW_REPORT_OPTION) {
                System.out.println("Enter the dentist's name:");
                scanner.nextLine();
                String dentistName  = scanner.nextLine();
                Dentist dentist = new Dentist(dentistName );
                Appointment[] report = service.reports(dentist);
                int reportSize = service.getReportSize();
                if (reportSize == 0) {
                    System.out.println("The dentist does not have any appointments");
                } else {
                    for (int i = 0; i < reportSize; i++) {
                        System.out.println(report[i]);
                    }
                }
            } else if (userChoice == EXIT_OPTION) {
                System.out.println("Now exiting...");
                CheckIfUserWantToExitFromMenu = false;
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