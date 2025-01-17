package repository;

import domain.Bacteria;
import org.sqlite.SQLiteDataSource;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class Repository {
    private static final String JDBC_URL = "jdbc:sqlite:data/test_db.db";
    protected List<Bacteria> bacterias = new ArrayList<>();

    public Repository() {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement statement =
                    conn.prepareStatement("SELECT * from bacterias");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String name = resultSet.getString(1);
                String category = resultSet.getString(2);
                String description = resultSet.getString(3);
                String symptoms = resultSet.getString(4);
                Bacteria bacteria = new Bacteria(name, category, description, symptoms);
                bacterias.add(bacteria);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Bacteria> getAllBacterias() {
        return bacterias;
    }

    public void deleteBacteria(String name) {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement deleteStatement =
                    conn.prepareStatement("DELETE FROM bacterias WHERE name = ?");
            deleteStatement.setString(1, name);
            deleteStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
