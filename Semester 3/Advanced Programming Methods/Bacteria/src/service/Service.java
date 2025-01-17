package service;

import domain.Bacteria;
import repository.Repository;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class Service {
    private Repository repo;

    public Service(Repository repo) {
        this.repo = repo;
    }

    public List<Bacteria> getAllBacterias() {
        return  repo.getAllBacterias().stream().sorted(Comparator.comparing(Bacteria::getCategory)).collect(Collectors.toList());
    }

    public List<Bacteria> searchBacterias(String nameDescription) {
        return repo.getAllBacterias().stream()
                .filter(b -> b.getName().contains(nameDescription) || b.getDescription().contains(nameDescription))
                .collect(Collectors.toList());
    }

    public void deleteBacteria(String name) {
        repo.deleteBacteria(name);
    }
}
