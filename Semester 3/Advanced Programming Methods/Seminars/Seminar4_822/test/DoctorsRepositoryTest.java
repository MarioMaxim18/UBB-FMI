import Repository.DoctorsRepository;
import Repository.RepositoryException;
import domain.Doctor;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Iterator;

public class DoctorsRepositoryTest {
    DoctorsRepository repo;

    @BeforeEach
    public void setUp()
    {
        repo = new DoctorsRepository();
        try {
            repo.add(1, new Doctor(1, "John", "oftalmology", 8));
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }
    }

    @Test
    public void testAdd() {
        try {
            repo.add(2, new Doctor(2, "Michael", "oftalmology", 9));
            Iterable<Doctor> values = repo.getAll();
            int size = 0;
            for (Doctor d: values)
                size++;
            Assertions.assertEquals(size, 2);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }

        try {
            repo.add(2, new Doctor(2, "Michael", "oftalmology", 9));
        } catch (RepositoryException e) {
            Assertions.assertEquals(e.getMessage(), "An object with id 2 already exists.");
        }
    }
}
