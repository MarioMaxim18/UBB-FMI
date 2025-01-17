package repository;

import domain.Recipe;
import org.sqlite.SQLiteDataSource;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class Repository {
    private static final String JDBC_URL = "jdbc:sqlite:data/test_db.db";
    protected List<Recipe> recipes = new ArrayList<>();

    public Repository() {
        try (Connection conn = DriverManager.getConnection(JDBC_URL))
        {
            PreparedStatement statement =
                    conn.prepareStatement("SELECT * from recipes");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String name = resultSet.getString(1);
                String cuisine = resultSet.getString(2);
                String description = resultSet.getString(3);
                String ingredients = resultSet.getString(4);
                Recipe recipe = new Recipe(name, cuisine, description, ingredients);
                recipes.add(recipe);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Recipe> getAllRecipes() {
        return recipes;
    }

    public void updateRecipe(String description, Recipe recipe) {
        try (Connection conn = DriverManager.getConnection(JDBC_URL)) {
            PreparedStatement modifyStatement =
                    conn.prepareStatement("UPDATE recipes SET description = ? WHERE description = ?");
            modifyStatement.setString(1, description);
            modifyStatement.setString(2, recipe.getDescription());
            modifyStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        for (Recipe r : recipes) {
            if (r.equals(recipe)) {
                r.setDescription(description);
            }
        }
    }
}
