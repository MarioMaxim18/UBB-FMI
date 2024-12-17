import domain.Dentist;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class DentistTest {

    @Test
    void constructor_validInput_createsDentist() {
        Dentist dentist = new Dentist(1, "Matei", "Oral Surgery", 9.5);
        assertEquals(1, dentist.getId());
        assertEquals("Matei", dentist.getName());
        assertEquals("Oral Surgery", dentist.getSpecialty());
        assertEquals(9.5, dentist.getGrade());
    }

    @Test
    void setId_validId_updatesId() {
        Dentist dentist = new Dentist(1, "Matei", "Oral Surgery", 9.5);
        dentist.setId(2);
        assertEquals(2, dentist.getId());
    }

    @Test
    void setName_validName_updatesName() {
        Dentist dentist = new Dentist(1, "Matei", "Oral Surgery", 9.5);
        dentist.setName("Mario");
        assertEquals("Mario", dentist.getName());
    }

    @Test
    void setSpecialty_validSpecialty_updatesSpecialty() {
        Dentist dentist = new Dentist(1, "Matei", "Oral Surgery", 9.5);
        dentist.setSpecialty("Pediatric Dentistry");
        assertEquals("Pediatric Dentistry", dentist.getSpecialty());
    }

    @Test
    void setGrade_validGrade_updatesGrade() {
        Dentist dentist = new Dentist(1, "Matei", "Oral Surgery", 9.5);
        dentist.setGrade(8.0);
        assertEquals(8.0, dentist.getGrade());
    }

    @Test
    void toString_returnsCorrectStringRepresentation() {
        Dentist dentist = new Dentist(1, "Matei", "Oral Surgery", 9.5);
        String expected = "id: 1, name: Matei, specialty: Oral Surgery, grade: 9.5";
        assertEquals(expected, dentist.toString());
    }
}