package repository;

import domain.Compute;
import domain.Resource;
import domain.Storage;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Repository {
    protected ArrayList<Resource> listWithResources;

    public Repository() {
        this.listWithResources = new ArrayList<>();
    }

    public void addComputeResource(Compute resource) {
        listWithResources.add(resource);
    }

    public void addStorageResource(Storage resource) {
        listWithResources.add(resource);
    }

    public ArrayList<Resource> getResources() {
        return listWithResources.stream().sorted(Comparator.comparing(Resource::computeScore)).collect(Collectors.toCollection(ArrayList::new));
    }

    public void readFromFile(String filePath) {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length > 0) {
                    String type = parts[0];
                    String identifier = parts[1];
                    String expirationDate = parts[2];
                    if (type.equalsIgnoreCase("Compute")) {
                        int cores = Integer.parseInt(parts[3]);
                        Compute compute = new Compute(identifier, expirationDate, cores);
                        addComputeResource(compute);
                    } else if (type.equalsIgnoreCase("Storage")) {
                        int capacity = Integer.parseInt(parts[3]);
                        String storageType = parts[4];
                        Storage storage = new Storage(identifier, expirationDate, capacity, storageType);
                        addStorageResource(storage);
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }

    public ArrayList<Resource> getFilteredResources(int threshold) {
        String nextMonth = "2024-02-01";

        return listWithResources.stream().filter(resource -> {
                String expirationDate = resource.getExpirationDate();

                if (expirationDate.compareTo(nextMonth) < 0) {
                    if (resource instanceof Compute) {
                        return ((Compute) resource).getCores() > threshold;
                    } else if (resource instanceof Storage) {
                        return ((Storage) resource).getCapacity() > threshold;
                    }
                }
                return false;
            }).sorted((r1, r2) -> r2.getIdentifier().compareTo(r1.getIdentifier())).collect(Collectors.toCollection(ArrayList::new));
    }
}
