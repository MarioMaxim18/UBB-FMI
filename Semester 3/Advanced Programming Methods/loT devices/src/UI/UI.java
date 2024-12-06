package UI;

import domain.Sensor;
import domain.SmokeSensor;
import domain.TemperatureSensor;
import service.Service;

import java.util.ArrayList;
import java.util.Scanner;

public class UI {
    protected Service service;

    public UI(Service service) {
        this.service = service;
    }

    public void displayMenu() {
        System.out.println("1. Add a sensor");
        System.out.println("2. Show all sensors");
        System.out.println("3. Show all sensors cheaper than a given value, that emit alerts");
        System.out.println("4. Save all sensors to file");
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
                    System.out.println("Enter sensor type:");
                    System.out.println("1. For temperature");
                    System.out.println("2. For smoke");
                    int type = scanner.nextInt();
                    scanner.nextLine();
                    if (type == 1) {
                        try {
                            System.out.println("Enter producer: ");
                            String producer = scanner.nextLine();
                            System.out.println("Enter last recording: ");
                            double lastRecording = scanner.nextDouble();
                            System.out.println("Enter diameter: ");
                            double diameter = scanner.nextDouble();
                            service.addTemperatureSensor(producer, lastRecording, diameter);
                        } catch (Exception e) {
                            System.out.println(e.getMessage());
                        }
                    } else if (type == 2) {
                        try{
                            System.out.println("Enter producer: ");
                            String producer = scanner.nextLine();
                            System.out.println("Enter last recording: ");
                            double lastRecording = scanner.nextDouble();
                            System.out.println("Enter length: ");
                            double length = scanner.nextDouble();
                            service.addSmokeSensor(producer, lastRecording, length);
                        } catch (Exception e) {
                            System.out.println(e.getMessage());
                        }
                    }
                    break;
                case 2:
                    ArrayList<Sensor> sensors = service.getSensors();
                    for (Sensor sensor : sensors) {
                        System.out.println(sensor);
                    }
                    break;
                case 3:
                    System.out.println("Enter price: ");
                    double price = scanner.nextDouble();
                    sensors = service.filteredSensors(price);
                    for (Sensor sensor : sensors) {
                        System.out.println(sensor);
                    }
                    break;
                case 4:
                    System.out.println("Enter producer: ");
                    String producer = scanner.nextLine();
                    service.saveToFile(producer);
                    break;
                case 0:
                    System.out.println("Exiting...");
                    exit = true;
                    break;
            }
        }
    }

    public void populateList() {
        service.addTemperatureSensor("Producer2", 8, 2);
        service.addTemperatureSensor("Producer1", 36, 4);
        service.addSmokeSensor("Producer1", 1599, 3);
        service.addSmokeSensor("Producer3", 1601, 2);
    }
}