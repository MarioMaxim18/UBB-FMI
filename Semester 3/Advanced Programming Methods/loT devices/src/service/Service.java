package service;

import domain.Sensor;
import domain.SmokeSensor;
import domain.TemperatureSensor;
import exceptions.ServiceException;
import repository.Repository;

import java.util.ArrayList;

public class Service {
    protected Repository repository;

    public Service(Repository repository) {
        this.repository = repository;
    }

    public void addTemperatureSensor(String producer, double lastRecording, double diameter) throws ServiceException {
        if (diameter > 0) {
            TemperatureSensor sensor = new TemperatureSensor(producer, lastRecording, diameter);
            repository.addTemperatureSensor(sensor);
        } else {
            throw new ServiceException("Diameter must be positive.");
        }
    }

    public void addSmokeSensor(String producer, double lastRecording, double length) throws ServiceException {
        if (length  > 0) {
            SmokeSensor sensor = new SmokeSensor(producer, lastRecording, length);
            repository.addSmokeSensor(sensor);
        } else {
             throw new ServiceException("Length must be positive.");
        }
    }

    public ArrayList<Sensor> getSensors() {
        return repository.getSensors();
    }

    public ArrayList<Sensor> filteredSensors(double givenPrice) {
        return repository.filteredSensors(givenPrice);
    }

    public void saveToFile(String producer) {
        repository.saveToFile(producer);
    }
}
