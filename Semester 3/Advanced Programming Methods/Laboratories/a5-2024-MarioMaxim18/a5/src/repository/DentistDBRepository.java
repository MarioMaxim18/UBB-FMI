package repository;

import domain.Dentist;

import java.sql.*;

public class DentistDBRepository extends MemoryRepository<Dentist> {
    public static String JDBC_URL = "jdbc:sqlite:data/dentistDB.sqlite";

    public DentistDBRepository() {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement statement =
                    conn.prepareStatement("SELECT * from dentists");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Integer id = resultSet.getInt(1);
                String name = resultSet.getString(2);
                String specialty = resultSet.getString(3);
                Double grade = resultSet.getDouble(4);
                Dentist dentist = new Dentist(id, name, specialty, grade);
                super.addDentist(id, dentist);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Dentist> getAllDentists() {
        return dentists.values();
    }

    @Override
    public void addDentist(int id, Dentist entity) throws RepositoryException {
        super.addDentist(id, entity);

        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement statement = conn.prepareStatement(
                    "INSERT INTO dentists VALUES (?,?,?,?)");
            statement.setInt(1, entity.getId());
            statement.setString(2, entity.getName());
            statement.setString(3, entity.getSpecialty());
            statement.setDouble(4, entity.getGrade());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void deleteDentist(int id) throws RepositoryException {
        super.deleteDentist(id);

        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement statement = conn.prepareStatement(
                    "DELETE FROM dentists WHERE id = ?");
            statement.setInt(1, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void modifyDentist(int id, Dentist newDentist) throws RepositoryException {
        super.modifyDentist(id, newDentist);

        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement statement = conn.prepareStatement(
                    "UPDATE dentists SET name = ?, specialty = ?, grade = ? WHERE id = ?");
            statement.setString(1, newDentist.getName());
            statement.setString(2, newDentist.getSpecialty());
            statement.setDouble(3, newDentist.getGrade());
            statement.setInt(4, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Dentist findByIdDentist(int id) throws RepositoryException {
        Dentist dentist = dentists.get(id);
        if (dentist == null) {
            throw new RepositoryException("Dentist with id " + id + " not found.");
        }
        return dentist;
    }
}
