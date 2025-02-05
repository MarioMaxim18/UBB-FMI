package gui;

import Repository.RepositoryException;
import domain.Doctor;
import Service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ListView;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;

import java.util.ArrayList;
import java.util.List;

public class Controller {
    private Service serv;
    ObservableList<Doctor> doctorsObservableList;

    @FXML
    private ListView<Doctor> listViewDoctors;

    @FXML
    private Button addButton;

    @FXML
    private TextField gradeTextField;

    @FXML
    private TextField idTextField;

    @FXML
    private TextField nameTextField;

    @FXML
    private TextField specialtyTextField;

    @FXML
    private TextField serchTextField;

    public Controller(Service serv) {
        this.serv = serv;
    }

    public void initialize() {
        doctorsObservableList = FXCollections.observableArrayList();
        Iterable<Doctor> allDoctors = serv.getDoctors();
        for (Doctor d: allDoctors)
            doctorsObservableList.add(d);
        listViewDoctors.setItems(doctorsObservableList);
    }

    @FXML
    void addButtonHandler(ActionEvent event) {
        Integer id = Integer.parseInt(idTextField.getText());
        String name = nameTextField.getText();
        String specialty = specialtyTextField.getText();
        Double grade = Double.parseDouble(gradeTextField.getText());
        try {
            serv.add(id, name, specialty, grade);
            doctorsObservableList.add(new Doctor(id, name, specialty, grade));
        }
        catch (RepositoryException e)
        {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    void handlerSearch(KeyEvent event) {
        String searchString = serchTextField.getText();
        List<Doctor> filteredDoctors = serv.getFilteredDoctors(searchString);
        doctorsObservableList.clear();
        for (Doctor d: filteredDoctors)
            doctorsObservableList.add(d);
    }
}
