package service;

import domain.Cardio;
import domain.Equipment;
import domain.Strength;
import exceptions.ServiceException;
import repository.Repository;

import java.util.ArrayList;
import java.util.Objects;

public class Service {
    protected Repository repository;

    public Service(Repository repository) {
        this.repository = repository;
    }

    public void addCardioEquipment(int serialNumber, boolean maintenance, int resistance) {
        Cardio equipment = new Cardio(serialNumber, maintenance, resistance);
        repository.addCardioEquipment(equipment);
    }

    public void addStrengthEquipment(int serialNumber, boolean maintenance, int motionLevel, String muscleGroup) throws ServiceException {
        if (Objects.equals(muscleGroup, "arms") || Objects.equals(muscleGroup, "legs") || Objects.equals(muscleGroup, "core")) {
            Strength equipment = new Strength(serialNumber, maintenance, motionLevel, muscleGroup);
            repository.addStrengthEquipment(equipment);
        } else {
            throw new ServiceException("Muscle group can be only legs, arms or core");
        }
    }

    public ArrayList<Equipment> getAllEquipments() {
        return repository.getAllEquipments();
    }

    public ArrayList<Equipment> filteredEquipments(double price, int givenValue) {
        return repository.filteredEquipments(price, givenValue);
    }

    public void saveToFile() {
        repository.saveToFile();
    }
}
