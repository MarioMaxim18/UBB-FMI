package service;

import domain.Compute;
import domain.Resource;
import domain.Storage;
import exceptions.ServiceException;
import repository.Repository;

import java.util.ArrayList;
import java.util.Objects;

public class Service {
    protected Repository repository;

    public Service(Repository repository) {
        this.repository = repository;
    }

    public void addComputeResource(String identifier, String expirationDate, int cores) {
        Compute resource = new Compute(identifier, expirationDate, cores);
        repository.addComputeResource(resource);
    }

    public void addStorageResource(String identifier, String expirationDate, int capacity, String type) throws ServiceException {
        if (Objects.equals(type, "HDD") || Objects.equals(type, "SSD") || Objects.equals(type, "Hybrid")) {
            Storage resource = new Storage(identifier, expirationDate, capacity, type);
            repository.addStorageResource(resource);
        } else {
            throw new ServiceException("Type can be only HDD, SSD or Hybrid");
        }
    }

    public ArrayList<Resource> getResources() {
        return repository.getResources();
    }

    public void readFromFile(String filePath) {
        repository.readFromFile(filePath);
    }

    public ArrayList<Resource> getFilteredResources(int threshold) {
        return repository.getFilteredResources(threshold);
    }
}
