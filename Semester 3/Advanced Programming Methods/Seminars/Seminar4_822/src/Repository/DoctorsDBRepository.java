package Repository;

import domain.Doctor;

import java.sql.*;

public class DoctorsDBRepository extends DoctorsRepository {
    public static String JDBC_URL = "jdbc:sqlite:data/doctorsDB.sqlite";

    @Override
    public Iterable<Doctor> getAll() {
//        this.entities.clear();
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement statement =
                    conn.prepareStatement("SELECT * from doctors");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Integer id = resultSet.getInt(1);
                String name = resultSet.getString(2);
                String specialty = resultSet.getString(3);
                Double grade = resultSet.getDouble(4);
                Doctor doctor = new Doctor(id, name, specialty, grade);
                super.add(id, doctor);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }

        return entities.values();
    }
}
