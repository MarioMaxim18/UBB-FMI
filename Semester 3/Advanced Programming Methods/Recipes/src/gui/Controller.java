package gui;

import domain.Recipe;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import service.Service;

import java.util.List;
import java.util.stream.Collectors;

public class Controller {
    private Service service;
    ObservableList<Recipe> recipesObservableList;

    @FXML
    private ListView<Recipe> listViewRecipes;

    @FXML
    private ComboBox<String> comboBoxCuisine;

    @FXML
    private TextField searchTextField;

    @FXML
    private Button buttonSearch;

    @FXML
    private Button buttonUpdate;

    @FXML
    private TextField updateTextField;

    @FXML
    private TextField findTextField;

    @FXML
    private Button buttonFind;

    @FXML
    private Label emptyLabel;

    public Controller(Service service) {
        this.service = service;
    }

    public void initialize() {
        List<Recipe> recipes  = service.getAllRecipes();
        recipesObservableList = FXCollections.observableList(recipes);
        listViewRecipes.setItems(FXCollections.observableList(recipesObservableList));
        List<String> cousines = recipes.stream().map(Recipe::getCuisine).distinct().collect(Collectors.toList());
        comboBoxCuisine.setItems(FXCollections.observableList(cousines));
    }

    @FXML
    void searchHandler(ActionEvent event) {
        String cuisines = comboBoxCuisine.getValue();
        String searchText = searchTextField.getText();
        List<Recipe> filteredRecipes = service.searchRecipes(cuisines, searchText);
        recipesObservableList = FXCollections.observableList(filteredRecipes);
        listViewRecipes.setItems(FXCollections.observableList(recipesObservableList));
    }

    @FXML
    void updateHandler(ActionEvent event) {
        String description = updateTextField.getText();
        Recipe recipe = listViewRecipes.getSelectionModel().getSelectedItem();
        service.updateRecipe(description, recipe);

        List<Recipe> updatedRecipes = service.getAllRecipes();
        recipesObservableList.setAll(updatedRecipes);
        listViewRecipes.refresh();
    }

    @FXML
    void findHandler(ActionEvent event) {
        String findText = findTextField.getText();
        List<Recipe> recipes = service.getAllRecipes();
        List<Recipe> foundRecipe = service.findRecipe(findText);
        if (foundRecipe.isEmpty()) {
            emptyLabel.setText("No recipes found");
        } else {
            recipesObservableList = FXCollections.observableList(foundRecipe);
            listViewRecipes.setItems(FXCollections.observableList(recipesObservableList));
        }
    }
}
