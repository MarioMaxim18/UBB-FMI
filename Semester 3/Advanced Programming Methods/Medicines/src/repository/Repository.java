package repository;

import domain.Medicine;
import org.sqlite.SQLiteDataSource;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class Repository {
    private static final String JDBC_URL = "jdbc:sqlite:data/test_db.db";
    protected List<Medicine> medicines = new ArrayList<>();

    public Repository() {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement statement =
                    conn.prepareStatement("SELECT * from medicines");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String name = resultSet.getString(1);
                String category = resultSet.getString(2);
                String description = resultSet.getString(3);
                String effects = resultSet.getString(4);
                Medicine medicine = new Medicine(name, category, description, effects);
                medicines.add(medicine);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Medicine> getAllMedicines() {
        return medicines;
    }

    public void deleteMedicine(String name) {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement deleteStatement =
                    conn.prepareStatement("DELETE FROM medicines WHERE name = ?");
            deleteStatement.setString(1, name);
            deleteStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
