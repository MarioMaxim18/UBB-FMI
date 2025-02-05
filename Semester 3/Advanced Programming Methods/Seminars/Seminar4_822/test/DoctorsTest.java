import domain.Doctor;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class DoctorsTest {
    private Doctor doctor;

    @BeforeEach
    public void setUp() {
        doctor = new Doctor(1, "Anna", "oftalmology", 9);
    }

    @Test
    public void testGetName() {
        Assertions.assertEquals(doctor.getName(), "Anna");
    }
}
