package UI;

import domain.Resource;
import service.Service;

import java.util.ArrayList;
import java.util.Scanner;

public class UI {
    protected Service service;

    public UI(Service service) {
        this.service = service;
    }

    public void displayMenu() {
        System.out.println("1. Add a resource");
        System.out.println("2. Show all resources sorted by utilization score");
        System.out.println("3. Show all resources having CPU cores/capacity greater than a given value");
        System.out.println("0. Exit");
    }

    public void run() {
        service.readFromFile("input.txt");
        boolean exit = false;
        Scanner scanner = new Scanner(System.in);
        while (!exit) {
            displayMenu();
            int choice = scanner.nextInt();
            scanner.nextLine();
            switch (choice) {
                case 1:
                    System.out.println("Enter compute type:");
                    System.out.println("1. For a compute resource");
                    System.out.println("2. For a storage resource");
                    int option = scanner.nextInt();
                    scanner.nextLine();
                    if (option == 1) {
                        System.out.println("Enter identifier: ");
                        String identifier = scanner.nextLine();
                        System.out.println("Enter expiration date: ");
                        String expirationDate = scanner.nextLine();
                        System.out.println("Enter number of cores: ");
                        int cores = scanner.nextInt();
                        service.addComputeResource(identifier, expirationDate, cores);
                    } else if (option == 2) {
                        try{
                            System.out.println("Enter identifier: ");
                            String identifier = scanner.nextLine();
                            System.out.println("Enter expiration date: ");
                            String expirationDate = scanner.nextLine();
                            System.out.println("Enter capacity: ");
                            int capacity = scanner.nextInt();
                            System.out.println("Enter type: ");
                            scanner.nextLine();
                            String type = scanner.nextLine();
                            service.addStorageResource(identifier, expirationDate, capacity, type);
                        } catch (Exception e) {
                            System.out.println(e.getMessage());
                        }
                    }
                    break;
                case 2:
                    ArrayList<Resource> resources = service.getResources();
                    for (Resource resource : resources) {
                        System.out.println(resource);
                    }
                    break;
                case 3:
                    System.out.println("Enter the threshold for CPU cores or capacity: ");
                    int threshold = scanner.nextInt();
                    scanner.nextLine();
                    ArrayList<Resource> filteredResources = service.getFilteredResources(threshold);
                    System.out.println("Filtered Resources:");
                    for (Resource resource : filteredResources) {
                        System.out.println(resource);
                    }
                    break;
                case 0:
                    System.out.println("Exiting...");
                    exit = true;
                    break;
            }
        }
    }
}