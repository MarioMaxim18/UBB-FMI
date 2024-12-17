import domain.Dentist;
import domain.Identifiable;
import filter.FilterDentistBySpecialty;
import repository.FakeRepo;
import repository.FilteredRepository;
import service.Service;
import repository.RepositoryException;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

import java.util.ArrayList;
import java.util.List;

public class DentistServiceTest {

    FakeRepo fakeRepo;
    Service service;

    @BeforeEach
    public void setUp() {
        fakeRepo = new FakeRepo();
        service = new Service<>(fakeRepo);
    }

    @Test
    public void testFindByIdDentist_validId_returnsCorrectDentist() throws RepositoryException {
        int dentistId = 1;

        Dentist dentist = (Dentist) service.getDentist(dentistId);

        Assertions.assertNotNull(dentist);
        Assertions.assertEquals(dentistId, dentist.getId());
        Assertions.assertEquals("Matei", dentist.getName());
        Assertions.assertEquals("Orthodontist", dentist.getSpecialty());
        Assertions.assertEquals(4.5, dentist.getGrade());
    }

    @Test
    public void testFilterDentistsBySpecialty_validSpecialty_returnsMatchingDentists() throws RepositoryException {
        String specialty = "Orthodontist";
        List<Dentist> actualOutput = service.filterDentistsBySpecialty(specialty);
        List<Dentist> expectedOutput = new ArrayList<>();
        expectedOutput.add(new Dentist(1, "Matei", "Orthodontist", 4.5));
        for (int i = 0; i < expectedOutput.size(); i++) {
            Dentist expectedDentist = expectedOutput.get(i);
            Dentist actualDentist = actualOutput.get(i);

            Assertions.assertEquals(expectedDentist.getId(), actualDentist.getId());
            Assertions.assertEquals(expectedDentist.getName(), actualDentist.getName());
            Assertions.assertEquals(expectedDentist.getSpecialty(), actualDentist.getSpecialty());
            Assertions.assertEquals(expectedDentist.getGrade(), actualDentist.getGrade());
        }
    }
}