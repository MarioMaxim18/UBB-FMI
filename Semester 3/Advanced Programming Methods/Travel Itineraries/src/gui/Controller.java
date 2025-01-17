package gui;

import domain.Itinerary;
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
    ObservableList<Itinerary> itinerariesObservableList;

    @FXML
    private ListView<Itinerary> listViewItineraries;


    @FXML
    private ComboBox<String> comboBoxContinent;

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
        List<Itinerary> Itineraries  = service.getAllItineraries();
        itinerariesObservableList = FXCollections.observableList(Itineraries);
        listViewItineraries.setItems(FXCollections.observableList(itinerariesObservableList));
        List<String> continents = Itineraries.stream().map(Itinerary::getContinent).distinct().collect(Collectors.toList());
        comboBoxContinent.setItems(FXCollections.observableList(continents));
    }

    @FXML
    void searchHandler(ActionEvent event) {
        String continent = comboBoxContinent.getValue();
        String searchText = searchTextField.getText();
        List<Itinerary> filteredItineraries = service.searchItineraries(continent, searchText);
        itinerariesObservableList = FXCollections.observableList(filteredItineraries);
        listViewItineraries.setItems(FXCollections.observableList(itinerariesObservableList));
    }

    @FXML
    void updateHandler(ActionEvent event) {
        String description = updateTextField.getText();
        Itinerary itinerary = listViewItineraries.getSelectionModel().getSelectedItem();
        service.updateItinerary(description, itinerary);

        List<Itinerary> updatedRecipes = service.getAllItineraries();
        itinerariesObservableList.setAll(updatedRecipes);
        listViewItineraries.refresh();
    }

    @FXML
    void findHandler(ActionEvent event) {
        String findText = findTextField.getText();
        List<Itinerary> recipes = service.getAllItineraries();
        List<Itinerary> foundRecipe = service.findItinerary(findText);
        if (foundRecipe.isEmpty()) {
            emptyLabel.setText("No itinerary found");
        } else {
            itinerariesObservableList = FXCollections.observableList(foundRecipe);
            listViewItineraries.setItems(FXCollections.observableList(itinerariesObservableList));
        }
    }
}
