package service;

import domain.Medicine;
import repository.Repository;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class Service {
    private Repository repo;

    public Service(Repository repo) {
        this.repo = repo;
    }

    public List<Medicine> getAllMedicines() {
        return  repo.getAllMedicines().stream().sorted(Comparator.comparing(Medicine::getCategory)).collect(Collectors.toList());
    }

    public List<Medicine> searchMedicines(String nameDescription) {
        return repo.getAllMedicines().stream()
                .filter(m -> m.getName().contains(nameDescription) || m.getDescription().contains(nameDescription))
                .collect(Collectors.toList());
    }

    public void deleteMedicine(String name) {
        repo.deleteMedicine(name);
    }

    public List<Medicine> topSideEffects() {

    }
}
