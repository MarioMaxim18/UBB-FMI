import repository.MemoryRepository;
import domain.Dentist;
import repository.RepositoryException;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class DentistRepositoryTest {

    MemoryRepository<Dentist> repo;

    @BeforeEach
    public void setUp() throws RepositoryException {
        repo = new MemoryRepository<>();
        repo.addDentist(1, new Dentist(1, "Andrei", "Orthodontist", 10));
    }

    @Test
    public void addDentist_validDentist_addsSuccessfully() throws RepositoryException {
        repo.addDentist(2, new Dentist(2, "Matei", "Pediatric Dentist", 8));
        Dentist dentist = repo.findByIdDentist(2);
        Assertions.assertNotNull(dentist);
        Assertions.assertEquals(dentist.getName(), "Matei");
        Assertions.assertEquals(dentist.getSpecialty(), "Pediatric Dentist");
    }

    @Test
    public void addDentist_duplicateId_throwsException() {
        try {
            repo.addDentist(1, new Dentist(1, "Mario", "General Dentist", 5));
        } catch (RepositoryException e) {
            Assertions.assertEquals(e.getMessage(), "A dentist with id 1 already exists.");
        }
    }

    @Test
    public void modifyDentist_validId_modifiesSuccessfully() throws RepositoryException{
        Dentist modifiedDentist = new Dentist(1, "Matei", "Oral Surgeon", 12);
        repo.modifyDentist(1, modifiedDentist);
        Dentist dentist = repo.findByIdDentist(1);
        Assertions.assertNotNull(dentist);
        Assertions.assertEquals(dentist.getSpecialty(), "Oral Surgeon");
        Assertions.assertEquals(dentist.getGrade(), 12);
    }

    @Test
    public void getAllDentists_Dentists_returnsAll() throws RepositoryException {
        repo.addDentist(2, new Dentist(2, "Matei", "Pediatric Dentist", 8));
        Iterable<Dentist> dentists = repo.getAllDentists();
        int size = 0;
        for (Dentist d : dentists) {
            size++;
        }
        Assertions.assertEquals(size, 2);
    }

    @Test
    public void generateUniqueIDforDentist_returnsUniqueId() {
        int id1 = repo.generateUniqueIDforDentist();
        int id2 = repo.generateUniqueIDforDentist();
        Assertions.assertNotEquals(id1, id2);
    }
}