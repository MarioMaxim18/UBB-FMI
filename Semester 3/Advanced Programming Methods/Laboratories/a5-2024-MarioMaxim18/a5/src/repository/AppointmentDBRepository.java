package repository;

import domain.Appointment;
import domain.Dentist;

import java.sql.*;

public class AppointmentDBRepository extends  MemoryRepository<Appointment> {
    public static String JDBC_URL = "jdbc:sqlite:data/appointmentDB.sqlite";

    public AppointmentDBRepository(DentistDBRepository dentistRepository) {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement statement =
                    conn.prepareStatement("SELECT * from appointments");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Integer dentistID = resultSet.getInt(1);
                Integer id = resultSet.getInt(2);
                Integer time = resultSet.getInt(3);
                Appointment appointment = new Appointment(dentistRepository.findByIdDentist(dentistID), id, time);
                super.addAppointment(id, appointment);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Appointment> getAllAppointments() {
        return appointments.values();
    }

    @Override
    public void addAppointment(int id, Appointment entity) throws RepositoryException {
        super.addAppointment(id, entity);

        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement statement = conn.prepareStatement(
                    "INSERT INTO appointments VALUES (?,?,?)");
            statement.setInt(1, entity.getDentist().getId());
            statement.setInt(2, entity.getId());
            statement.setInt(3, entity.getTime());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void deleteAppointment(int id) {
        super.deleteAppointment(id);

        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement statement = conn.prepareStatement(
                    "DELETE FROM appointments WHERE id = ?");
            statement.setInt(1, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void modifyAppointment(int id, Appointment entity) {
        super.modifyAppointment(id, entity);

        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement statement = conn.prepareStatement(
                    "UPDATE appointments SET dentistID = ?, time = ? WHERE id = ?");
            statement.setInt(1, entity.getDentist().getId());
            statement.setInt(2, entity.getTime());
            statement.setInt(3, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
