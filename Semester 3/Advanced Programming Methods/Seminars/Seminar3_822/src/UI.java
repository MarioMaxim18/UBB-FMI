import Repository.*;
import Service.Service;

import java.util.Scanner;

public class UI {
    private Service serv;

    public UI(Service serv) {
        this.serv = serv;
    }

    void printMenu() {
        System.out.println("1 - Add doctor.");
        System.out.println("2 - Print all doctors.");
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
                case 0:
                        return;
            }
        }
    }

    public static void main(String[] args) {
        Repository repo = new Repository();
        Service serv = new Service(repo);
        UI ui = new UI(serv);
        ui.run();
    }
}
