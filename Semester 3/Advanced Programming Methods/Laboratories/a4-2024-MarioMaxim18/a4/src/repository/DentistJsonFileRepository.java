package repository;

import com.fasterxml.jackson.databind.DatabindException;
import com.fasterxml.jackson.databind.ObjectMapper;
import domain.Dentist;
import domain.Identifiable;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class DentistJsonFileRepository extends MemoryRepository<Dentist> {
    private String filePath;
    private ObjectMapper objectMapper;

    public DentistJsonFileRepository(String filePath) {
        this.filePath = filePath;
        this.objectMapper = new ObjectMapper();
        loadFromFile();
    }

    @Override
    public void addDentist(int id, Dentist dentist) throws RepositoryException {
        super.addDentist(id, dentist);
        saveToFile();
    }

    @Override
    public void modifyDentist(int id, Dentist dentist) throws RepositoryException {
        super.modifyDentist(id, dentist);
        saveToFile();
    }

    @Override
    public void deleteDentist(int id) throws RepositoryException {
        super.deleteDentist(id);
        saveToFile();
    }

    @Override
    public Iterable<Dentist> getAllDentists() {
        return super.getAllDentists();
    }

    private void loadFromFile() {
        try {
            File file = new File(filePath);
            if (file.exists()) {
                List<Dentist> dentistsFromFile = objectMapper.readValue(
                        file,
                        objectMapper.getTypeFactory().constructCollectionType(List.class, Dentist.class)
                );
                for (Dentist dentist : dentistsFromFile) {
                    dentists.put(dentist.getId(), dentist);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveToFile() {
        try {
            List<Dentist> dentistList = dentists.values().stream().collect(Collectors.toList());
            objectMapper.writeValue(new File(filePath), dentistList);  // Write to the JSON file
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}