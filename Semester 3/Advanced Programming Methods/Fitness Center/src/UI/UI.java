package UI;

import domain.Equipment;
import service.Service;

import java.util.ArrayList;
import java.util.Scanner;

public class UI {
    protected Service service;

    public UI(Service service) {
        this.service = service;
    }

    public void displayMenu() {
        System.out.println("1. Add a training machine");
        System.out.println("2. Show all training machines");
        System.out.println("3. Show all training machines cheaper than a given value, having the resistance/motion level greater than a given value");
        System.out.println("4. Save all training machines to file");
        System.out.println("0. Exit");
    }

    public void run() {
        populateList();
        boolean exit = false;
        Scanner scanner = new Scanner(System.in);
        while (!exit) {
            displayMenu();
            int choice = scanner.nextInt();
            scanner.nextLine();
            switch (choice) {
                case 1:
                    System.out.println("Enter training machine type:");
                    System.out.println("1. Cardio machine");
                    System.out.println("2. Strength training machine");
                    int type = scanner.nextInt();
                    scanner.nextLine();
                    if (type == 1) {
                        try {
                            System.out.println("Enter serial number: ");
                            int serialNumber= scanner.nextInt();
                            System.out.println("Requires regular maintenance: ");
                            boolean maintenance = scanner.nextBoolean();
                            System.out.println("Enter resistance level: ");
                            int resistance= scanner.nextInt();
                            service.addCardioEquipment(serialNumber, maintenance, resistance);
                        } catch (Exception e) {
                            System.out.println(e.getMessage());
                        }
                    } else if (type == 2) {
                        try{
                            System.out.println("Enter serial number: ");
                            int serialNumber= scanner.nextInt();
                            System.out.println("Requires regular maintenance: ");
                            boolean maintenance = scanner.nextBoolean();
                            System.out.println("Enter motion level: ");
                            int motionLevel = scanner.nextInt();
                            System.out.println("Enter muscle group: ");
                            scanner.nextLine();
                            String muscleGroup = scanner.nextLine();
                            service.addStrengthEquipment(serialNumber,maintenance, motionLevel, muscleGroup);
                        } catch (Exception e) {
                            System.out.println(e.getMessage());
                        }
                    }
                    break;
                case 2:
                    ArrayList<Equipment> equipments = service.getAllEquipments();
                    for (Equipment equipment : equipments) {
                        System.out.println(equipment);
                    }
                    break;
                case 3:
                    System.out.println("Enter price: ");
                    double price = scanner.nextDouble();
                    System.out.println("resistance/motion level: ");
                    int givenValue = scanner.nextInt();
                    equipments = service.filteredEquipments(price, givenValue);
                    for (Equipment equipment : equipments) {
                        System.out.println(equipment);
                    }
                    break;
                case 4:
                    service.saveToFile();
                    break;
                case 0:
                    System.out.println("Exiting...");
                    exit = true;
                    break;
            }
        }
    }

    public void populateList() {
        service.addCardioEquipment(1, true, 12);
        service.addCardioEquipment(2, false, 2);
        service.addStrengthEquipment(3, true, 32, "legs");
        service.addStrengthEquipment(4, true, 2, "core");
    }
}