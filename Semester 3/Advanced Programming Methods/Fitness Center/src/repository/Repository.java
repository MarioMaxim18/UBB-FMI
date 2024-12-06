package repository;

import domain.Equipment;
import domain.Cardio;
import domain.Strength;

import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Properties;
import java.util.stream.Collectors;

public class Repository {
    protected ArrayList<Equipment> listWithEquipments;

    public Repository() {
        this.listWithEquipments = new ArrayList<>();
    }

    public void addCardioEquipment(Cardio equipment) {
        listWithEquipments.add(equipment);
    }

    public void addStrengthEquipment(Strength equipment) {
        listWithEquipments.add(equipment);
    }

    public ArrayList<Equipment> getAllEquipments() {
        return listWithEquipments;
    }

    public ArrayList<Equipment> filteredEquipments(double price, int givenValue) {
        return listWithEquipments.stream().filter(equipment -> equipment.computePrice() < price && (equipment instanceof Cardio && ((Cardio) equipment).getResistance() > givenValue) || (equipment instanceof Strength && ((Strength) equipment).getMotionLevel()> givenValue)).sorted(Comparator.comparingInt(Equipment::getSerialNumber).reversed()).collect(Collectors.toCollection(ArrayList::new));
    }

    public void saveToFile(){
        FileReader fileToWrite = null;
        try {
            fileToWrite = new FileReader("settings.properties");
            Properties prop = new Properties();
            prop.load(fileToWrite);

            String fileName = (String) prop.get("fileName");
            String filePath = prop.getProperty("filePath");

            ArrayList<Equipment> filteredEquipments = listWithEquipments.stream().filter(Equipment::getMaintenance).sorted((Comparator.comparingDouble(Equipment::computePrice).reversed())).collect(Collectors.toCollection(ArrayList::new));
            BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
            for (Equipment sensor : filteredEquipments) {
                writer.write(sensor.toString());
                writer.newLine();
            }
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
