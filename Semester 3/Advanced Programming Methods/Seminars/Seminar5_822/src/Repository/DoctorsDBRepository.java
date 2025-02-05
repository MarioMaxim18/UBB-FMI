package Repository;

import domain.Doctor;

import java.sql.*;

public class DoctorsDBRepository extends DoctorsRepository {
    public static String JDBC_URL = "jdbc:sqlite:data/doctorsDB.sqlite";

    public DoctorsDBRepository()
    {
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
    }

    @Override
    public void add(Integer id, Doctor entity) throws RepositoryException {
        super.add(id, entity);

        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement statement = conn.prepareStatement(
                    "INSERT INTO doctors VALUES (?,?,?,?)");
            statement.setInt(1, entity.getID());
            statement.setString(2, entity.getName());
            statement.setString(3, entity.getSpecialty());
            statement.setDouble(4, entity.getGrade());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
