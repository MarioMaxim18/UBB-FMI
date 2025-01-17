package gui;

import domain.Medicine;
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
    ObservableList<Medicine> medicinesObservableList = FXCollections.observableArrayList();

    @FXML
    private ListView<Medicine> listViewMedicines;

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
        medicinesObservableList.addAll(service.getAllMedicines());
        listViewMedicines.setItems(medicinesObservableList);
        searchCategory.textProperty().addListener((observable, oldValue, newValue) -> filterMedicinesByCategory());
    }

    private void filterMedicinesByCategory() {
        String categoryFilter = searchCategory.getText().toLowerCase();

        List<Medicine> filteredMedicines = service.getAllMedicines().stream()
                .filter(medicine -> medicine.getCategory().toLowerCase().contains(categoryFilter))
                .collect(Collectors.toList());

        medicinesObservableList.setAll(filteredMedicines);
    }

    @FXML
    void searchHandler(ActionEvent event) {
        String searchText = searchTextField.getText();
        List<Medicine> filteredMedicines = service.searchMedicines(searchText);
        medicinesObservableList = FXCollections.observableList(filteredMedicines);
        listViewMedicines.setItems(FXCollections.observableList(medicinesObservableList));
    }

    @FXML
    void deleteHandler(ActionEvent event) {
        Medicine selectedMedicine = listViewMedicines.getSelectionModel().getSelectedItem();
        service.deleteMedicine(selectedMedicine.getName());
        medicinesObservableList.remove(selectedMedicine);
    }

    @FXML
    void updateHandler(ActionEvent event) {

    }
}