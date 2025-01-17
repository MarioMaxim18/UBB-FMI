package repository;

import domain.Itinerary;
import org.sqlite.SQLiteDataSource;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class Repository {
    private static final String JDBC_URL = "jdbc:sqlite:data/test_db.db";
    protected List<Itinerary> itineraries = new ArrayList<>();

    public Repository() {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement statement =
                    conn.prepareStatement("SELECT * from Itinerary");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String name = resultSet.getString(1);
                String continent = resultSet.getString(2);
                String description = resultSet.getString(3);
                String placesToVisit = resultSet.getString(4);
                Itinerary Itinerary = new Itinerary(name, continent, description, placesToVisit);
                itineraries.add(Itinerary);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Itinerary> getAllItineraries() {
        return itineraries;
    }

    public void updateItinerary(String description, Itinerary itinerary) {
        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement modifyStatement =
                    conn.prepareStatement("UPDATE Itinerary SET description = ? WHERE description = ?");
            modifyStatement.setString(1, description);
            modifyStatement.setString(2, itinerary.getDescription());
            modifyStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        for (Itinerary i : itineraries) {
            if (i.equals(itinerary)) {
                i.setDescription(description);
            }
        }
    }
}
