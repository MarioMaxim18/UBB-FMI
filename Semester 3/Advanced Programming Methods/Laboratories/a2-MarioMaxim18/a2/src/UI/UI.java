package UI;

import domain.Appointment;
import domain.Dentist;
import domain.Identifiable;
import service.Service;

import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class UI {
    private static final int EXIT_OPTION = 0;
    private static final int ADD_APPOINTMENT_OPTION = 1;
    private static final int VIEW_APPOINTMENT_OPTION = 2;
    private static final int UPDATE_APPOINTMENT_OPTION = 3;
    private static final int CANCEL_APPOINTMENT_OPTION = 4;
    private static final int VIEW_REPORT_OPTION = 5;
    private static final int VIEW_ALL_DENTISTS_OPTION = 6;
    private static final int FILTER_APPOINTMENTS_BY_TIME_OPTION= 7;
    private static final int FILTER_DENTIST_BY_SPECIALTY_OPTION = 8;
    private static final int FILTER_DENTIST_BY_GRADE_OPTION = 9;

    private static final int PLACE_HOLDER_ID = 0;
    private static final String PLACE_HOLDER_SPECIALTY = "";
    private static final double PLACE_HOLDER_GRADE = 0;

    private static final int MIN_ID = 1;
    private static final int MIN_TIME = 1;
    private static final int MIN_GRADE = 1;
    private static final int MAX_GRADE = 10;

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
        System.out.println(VIEW_ALL_DENTISTS_OPTION + ". View all dentists");
        System.out.println(FILTER_APPOINTMENTS_BY_TIME_OPTION + ". Filter appointments by time");
        System.out.println(FILTER_DENTIST_BY_SPECIALTY_OPTION + ". Filter dentists by specialty");
        System.out.println(FILTER_DENTIST_BY_GRADE_OPTION + ". Filter dentists by grade");
        System.out.println();
        System.out.println(EXIT_OPTION + ". Exit");
    }

    public void run() {
        populateList();
        Scanner scanner = new Scanner(System.in);
        int appointmentID;
        int dentistID;
        int time;
        String dentistName;

        while (CheckIfUserWantToExitFromMenu) {
            displayMenu();
            System.out.println("Option:");

            int userChoice = scanner.nextInt();
            scanner.nextLine();

            switch (userChoice) {
                case ADD_APPOINTMENT_OPTION:
                    try {
                        appointmentID = service.generateUniqueIDforAppointment();
                        System.out.println("Generated appointment ID: " + appointmentID);

                        System.out.println("Enter the time:");
                        time = getValidTime(scanner);

                        dentistID = service.generateUniqueIDforDentist();
                        System.out.println("Generated dentist ID: " + dentistID);

                        System.out.println("Enter the dentist's name:");
                        dentistName = scanner.nextLine();

                        System.out.println("Enter the dentist's specialty:");
                        String dentistSpecialty = getValidSpecialty(scanner);

                        System.out.println("Enter the dentist's grade:");
                        double grade = getValidGrade(scanner);

                        Dentist newDentist = new Dentist(dentistID, dentistName, dentistSpecialty, grade);
                        service.addDentist(dentistID, dentistName, dentistSpecialty, grade);
                        service.addAppointment(newDentist, appointmentID, time);
                    } catch (Exception e) {
                        System.out.println("Error while adding appointment: " + e.getMessage());
                    }
                    break;

                case VIEW_APPOINTMENT_OPTION:
                    try {
                        System.out.println("Enter the appointment ID:");
                        appointmentID = getValidID(scanner);

                        Appointment appointment = service.getAppointment(appointmentID);
                        if (appointment == null) {
                            System.out.println("The ID does not exist.");
                        } else {
                            System.out.println(appointment);
                        }
                    } catch (Exception e) {
                        System.out.println("Error while viewing appointment: " + e.getMessage());
                    }
                    break;

                case UPDATE_APPOINTMENT_OPTION:
                    try {
                        System.out.println("Enter the appointment ID:");
                        appointmentID = getValidID(scanner);

                        System.out.println("Enter the new time:");
                        time = getValidTime(scanner);

                        service.updateAppointment(appointmentID, time);
                    } catch (Exception e) {
                        System.out.println("Error while updating appointment: " + e.getMessage());
                    }
                    break;

                case CANCEL_APPOINTMENT_OPTION:
                    try {
                        System.out.println("Enter the appointment ID:");
                        appointmentID = getValidID(scanner);

                        service.removeAppointment(appointmentID);
                        System.out.println("The appointment has been removed.");
                    } catch (Exception e) {
                        System.out.println("Error while cancelling appointment: " + e.getMessage());
                    }
                    break;

                case VIEW_REPORT_OPTION:
                    try {
                        System.out.println("Enter the dentist's name:");
                        dentistName = scanner.nextLine();

                        Dentist reportDentist = new Dentist(PLACE_HOLDER_ID, dentistName, PLACE_HOLDER_SPECIALTY, PLACE_HOLDER_GRADE);
                        List<Appointment> report = service.reports(reportDentist);
                        for (Appointment appointmentItem : report) {
                            System.out.println(appointmentItem);
                        }
                    } catch (Exception e) {
                        System.out.println("Error while viewing report: " + e.getMessage());
                    }
                    break;

                case VIEW_ALL_DENTISTS_OPTION:
                    try {
                        Iterable<Identifiable> allDentists = service.getAllDentists();
                        for (Identifiable dentist : allDentists) {
                            System.out.println(dentist.toString());
                        }
                    } catch (Exception e) {
                        System.out.println("Error while viewing all dentists: " + e.getMessage());
                    }
                    break;

                case FILTER_APPOINTMENTS_BY_TIME_OPTION:
                    try {
                        System.out.println("Enter the time:");
                        time = getValidTime(scanner);

                        List<Appointment> filteredAppointments = service.filterAppointmentsByTime(time);
                        for (Appointment appointmentItem : filteredAppointments) {
                            System.out.println(appointmentItem);
                        }
                    } catch (Exception e) {
                        System.out.println("Error while filtering appointments: " + e.getMessage());
                    }
                    break;

                case FILTER_DENTIST_BY_SPECIALTY_OPTION:
                    try {
                        System.out.println("Enter the specialty:");
                        String specialty = getValidSpecialty(scanner);

                        List<Dentist> filteredDentists = service.filterDentistsBySpecialty(specialty);
                        for (Dentist dentistItem : filteredDentists) {
                            System.out.println(dentistItem);
                        }
                    } catch (Exception e) {
                        System.out.println("Error while filtering dentists: " + e.getMessage());
                    }
                    break;

                case FILTER_DENTIST_BY_GRADE_OPTION:
                    try {
                        System.out.println("Enter the grade:");
                        double grade = getValidGrade(scanner);

                        List<Dentist> filteredDentists = service.filterDentistsByGrade(grade);
                        for (Dentist dentistItem : filteredDentists) {
                            System.out.println(dentistItem);
                        }
                    } catch (Exception e) {
                        System.out.println("Error while filtering dentists: " + e.getMessage());
                    }
                    break;

                case EXIT_OPTION:
                    System.out.println("Now exiting...");
                    CheckIfUserWantToExitFromMenu = false;
                    break;

                default:
                    System.out.println("Invalid option.");
                    break;
            }
        }
        scanner.close();
    }

    private int getValidID(Scanner scanner) {
        int id = -1;
        while (id < MIN_ID) {
            try {
                id = scanner.nextInt();
                scanner.nextLine();
                if (id < MIN_ID) {
                    System.out.println("Enter a positive integer ID.");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid ID.");
                scanner.nextLine();
            }
        }
        return id;
    }

    private int getValidTime(Scanner scanner) {
        int time = -1;
        while (time < MIN_TIME) {
            try {
                time = scanner.nextInt();
                scanner.nextLine();
                if (time < MIN_TIME) {
                    System.out.println("Enter a valid positive time.");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid time.");
                scanner.nextLine();
            }
        }
        return time;
    }

    private String getValidSpecialty(Scanner scanner) {
        String specialty = "";
        while (specialty.isEmpty()) {
            specialty = scanner.nextLine();
            if (specialty.isEmpty()) {
                System.out.println("Enter a valid specialty.");
            }
        }
        return specialty;
    }

    private double getValidGrade(Scanner scanner) {
        double grade = -1;
        while (grade < MIN_GRADE || grade > MAX_GRADE) {
            if (scanner.hasNextDouble()) {
                grade = scanner.nextDouble();
                if (grade < MIN_GRADE || grade > MAX_GRADE) {
                    System.out.println("Grade must be between " + MIN_GRADE + " and " + MAX_GRADE);
                }
            } else {
                System.out.println("Invalid input.");
                scanner.next();
            }
        }
        return grade;
    }

    void populateList() {
        service.addAppointment(new Dentist(1, "Mario", "Orthodontics", 10.0), 1, 10);
        service.addDentist(1, "Mario", "Orthodontics", 10.0);
        service.addAppointment(new Dentist(2, "Andrei", "Endodontics", 9.2), 2, 11);
        service.addDentist(2, "Andrei", "Endodontics", 9.2);
        service.addAppointment(new Dentist(3, "Andrei", "Periodontics", 8.3), 3, 8);
        service.addDentist(3, "Andrei", "Periodontics", 8.3);
        service.addAppointment(new Dentist(4, "Matei", "Oral Surgery", 3.1), 4, 11);
        service.addDentist(4, "Matei", "Oral Surgery", 12.1);
        service.addAppointment(new Dentist(5, "Matei", "Pediatric Dentistry", 9.2), 5, 9);
        service.addDentist(5, "Matei", "Pediatric Dentistry", 9.2);
        service.addAppointment(new Dentist(6, "Matei", "Pediatric Dentistry", 10.4), 6, 14);
        service.addDentist(6, "Matei", "Pediatric Dentistry", 10.4);
    }
}