package gui;

import domain.Bacteria;
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
    ObservableList<Bacteria> bacteriaObservableList  = FXCollections.observableArrayList();;

    @FXML
    private ListView<Bacteria> listViewBacterias;

    @FXML
    private TextField searchCategory;

    @FXML
    private TextField searchTextField;

    @FXML
    private Button buttonSearch;

    @FXML
    private Button buttonDelete;

    @FXML
    private Label emptyLabel;

    @FXML
    private Button buttonUpdate;

    public Controller(Service service) {
        this.service = service;
    }

    public void initialize() {
        bacteriaObservableList.addAll(service.getAllBacterias());
        listViewBacterias.setItems(bacteriaObservableList);
        searchCategory.textProperty().addListener((observable, oldValue, newValue) -> filterBacteriasByCategory());
    }

    private void filterBacteriasByCategory() {
        String categoryFilter = searchCategory.getText().toLowerCase();

        List<Bacteria> filteredBacterias = service.getAllBacterias().stream()
                .filter(bacteria -> bacteria.getCategory().toLowerCase().contains(categoryFilter))
                .collect(Collectors.toList());

        bacteriaObservableList.setAll(filteredBacterias);
        listViewBacterias.setItems(bacteriaObservableList);
    }

    @FXML
    void searchHandler(ActionEvent event) {
        String searchText = searchTextField.getText();
        List<Bacteria> filteredBacterias = service.searchBacterias(searchText);
        bacteriaObservableList = FXCollections.observableList(filteredBacterias);
        listViewBacterias.setItems(FXCollections.observableList(bacteriaObservableList));
    }

    @FXML
    void deleteHandler(ActionEvent event) {
        Bacteria selectedBacteria = listViewBacterias.getSelectionModel().getSelectedItem();

        Alert confirmationAlert = new Alert(Alert.AlertType.CONFIRMATION);
        confirmationAlert.setTitle("Delete Confirmation");
        confirmationAlert.setHeaderText("Are you sure?");
        confirmationAlert.setContentText("Name: " + selectedBacteria.getName() +
                "\nCategory: " + selectedBacteria.getCategory() +
                "\nDescription: " + selectedBacteria.getDescription());

        confirmationAlert.showAndWait().ifPresent(response -> {
            if (response == ButtonType.OK) {
                service.deleteBacteria(selectedBacteria.getName());
                bacteriaObservableList.remove(selectedBacteria);
            }
        });
    }
}
