package repository;

import domain.Sensor;
import domain.SmokeSensor;
import domain.TemperatureSensor;

import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Properties;
import java.util.stream.Collectors;

public class Repository {
    protected ArrayList<Sensor> listWithSensors;

    public Repository() {
        this.listWithSensors = new ArrayList<>();
    }

    public void addSmokeSensor(SmokeSensor sensor) {
        listWithSensors.add(sensor);
    }

    public void addTemperatureSensor(TemperatureSensor sensor) {
        listWithSensors.add(sensor);
    }

    public ArrayList<Sensor> getSensors() {
        return listWithSensors;
    }

    public ArrayList<Sensor> filteredSensors(double givenPrice) {
        return listWithSensors.stream().filter(sensor -> sensor.computePrice() < givenPrice && sensor.emitAlert()).sorted(Comparator.comparing(Sensor::getProducer)).collect(Collectors.toCollection(ArrayList::new));
    }

    public void saveToFile(String producer) {
        FileReader fileToWrite = null;
        try {
            fileToWrite = new FileReader("settings.properties");
            Properties prop = new Properties();
            prop.load(fileToWrite);

            String fileName = (String) prop.get("fileName");
            String filePath = prop.getProperty("filePath");

            ArrayList<Sensor> filteredSensors = listWithSensors.stream().filter(sensor -> sensor.getProducer().equals(producer)).sorted(Comparator.comparingDouble(Sensor::computePrice).reversed()).collect(Collectors.toCollection(ArrayList::new));
            BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
            for (Sensor sensor : filteredSensors) {
                writer.write(sensor.toString());
                writer.newLine();
            }
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
