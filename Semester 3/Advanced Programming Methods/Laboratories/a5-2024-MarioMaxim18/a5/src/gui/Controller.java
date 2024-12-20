package gui;

import domain.Appointment;
import javafx.scene.control.*;
import repository.RepositoryException;
import service.Service;
import domain.Dentist;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import java.util.List;
import java.util.Optional;

public class Controller {
    private Service service;
    ObservableList<Dentist> dentistsObservableList;
    ObservableList<Appointment> appointmentsObservableList;

    @FXML
    private ListView<Dentist> listViewDentists;

    @FXML
    private ListView<Appointment> listViewAppointments;

    @FXML
    private Button addButton;

    @FXML
    private Button updateButton;

    @FXML
    private Button deleteButton;

    @FXML
    private TextField gradeTextField;

    @FXML
    private TextField idTextField;

    @FXML
    private TextField nameTextField;

    @FXML
    private TextField specialtyTextField;

    @FXML
    private TextField dentistIDTextFieldAppointment;

    @FXML
    private TextField idTextFieldAppointment;

    @FXML
    private TextField timeTextFieldAppointment;

    @FXML
    private Button addButtonAppointment;

    @FXML
    private Button updateButtonAppointment;

    @FXML
    private Button deleteButtonAppointment;

    @FXML
    private Button sortByNameButton;

    @FXML
    private Button sortBySpecialtyButton;

    @FXML
    private Button sortByGradeButton;

    @FXML
    private Button sortByIdButton;

    @FXML
    private Button sortByIdButtonAppointment;

    @FXML
    private Button filterByTimeButton;

    @FXML
    private Button filterBySpecialtyButton;

    @FXML
    private Button filterByGradeButton;

    public Controller(Service service) {
        this.service = service;
    }

    public void initialize() throws RepositoryException {
        dentistsObservableList = FXCollections.observableArrayList();
        appointmentsObservableList = FXCollections.observableArrayList();
        Iterable<Appointment> allAppointments = service.getAllAppointments();
        Iterable<Dentist> allDentists = service.getAllDentists();
        for (Dentist dentist : allDentists)
            dentistsObservableList.add(dentist);
        for (Appointment appointment : allAppointments)
            appointmentsObservableList.add(appointment);
        listViewDentists.setItems(dentistsObservableList);
        listViewAppointments.setItems(appointmentsObservableList);
    }

    @FXML
    void addButtonHandler(ActionEvent event) {
        try {
            Integer id = Integer.parseInt(idTextField.getText());
            String name = nameTextField.getText();
            String specialty = specialtyTextField.getText();
            Double grade = Double.parseDouble(gradeTextField.getText());
            service.addDentist(id, name, specialty, grade);
            dentistsObservableList.add(new Dentist(id, name, specialty, grade));
            refreshLists();
        } catch (NumberFormatException e) {
            showError("Invalid input", "Please enter valid values");
        } catch (RepositoryException e) {
            showError("Error", e.getMessage());
        }
    }

    @FXML
    void deleteButtonHandler(ActionEvent event) {
        try {
            Integer id = Integer.parseInt(idTextField.getText());
            Dentist dentist = service.getDentist(id);
            service.deleteDentist(id);
            dentistsObservableList.remove(dentist);
        } catch (NumberFormatException e) {
            showError("Invalid ID", "Please enter a valid value for id dentist.");
        } catch (RepositoryException e) {
            showError("Error", e.getMessage());
        }
    }

    @FXML
    void updateButtonHandler(ActionEvent event) {
        try {
            Integer id = Integer.parseInt(idTextField.getText());
            String name = nameTextField.getText();
            String specialty = specialtyTextField.getText();
            Double grade = Double.parseDouble(gradeTextField.getText());

            Dentist dentist = service.getDentist(id);
            service.updateDentist(id, name, specialty, grade);
            dentistsObservableList.clear();
            Iterable<Dentist> allDentists = service.getAllDentists();
            for (Dentist d : allDentists)
                dentistsObservableList.add(d);
            listViewDentists.refresh();
        } catch (NumberFormatException e) {
            showError("Invalid Input", "Please enter valid values.");
        } catch (RepositoryException e) {
            showError("Error", e.getMessage());
        }
    }

    @FXML
    void addButtonHandlerAppointment(ActionEvent event) {
        try {
            Integer dentistId = Integer.parseInt(dentistIDTextFieldAppointment.getText());
            Integer id = Integer.parseInt(idTextFieldAppointment.getText());
            Integer time = Integer.parseInt(timeTextFieldAppointment.getText());

            Dentist dentist = service.getDentist(dentistId);
            service.addAppointment(dentist, id, time);
            appointmentsObservableList.add(new Appointment(dentist, id, time));
            refreshLists();
        } catch (NumberFormatException e) {
            showError("Invalid Input", "Please enter valid values.");
        } catch (RepositoryException e) {
            showError("Error", e.getMessage());
        }
    }

    @FXML
    void deleteButtonHandlerAppointment(ActionEvent event) {
        try {
            Integer id = Integer.parseInt(idTextFieldAppointment.getText());

            Appointment appointment = service.getAppointment(id);
            if (appointment == null) {
                showError("Appointment Not Found", "No appointment found with the specified ID.");
                return;
            }

            Dentist dentist = appointment.getDentist();
            if (dentist == null) {
                showError("Dentist Not Found", "The appointment does not have a valid associated dentist.");
                return;
            }

            service.removeAppointment(id);
            appointmentsObservableList.remove(appointment);
            listViewAppointments.refresh();

        } catch (NumberFormatException e) {
            showError("Invalid Input", "Please enter a valid numeric value for appointment ID.");
        } catch (RepositoryException e) {
            showError("Error", e.getMessage());
        }
    }

    @FXML
    void updateButtonHandlerAppointment(ActionEvent event) {
        try {
            Integer id = Integer.parseInt(idTextFieldAppointment.getText());
            Integer time = Integer.parseInt(timeTextFieldAppointment.getText());
            Integer dentistId = Integer.parseInt(dentistIDTextFieldAppointment.getText());

            Dentist dentist = service.getDentist(dentistId);
            if (dentist == null) {
                showError("Dentist Not Found", "No dentist found with the specified ID.");
                return;
            }

            Appointment appointment = service.getAppointment(id);
            if (appointment == null) {
                showError("Appointment Not Found", "No appointment found with the specified ID.");
                return;
            }

            service.updateAppointment(id, time);
            appointmentsObservableList.clear();
            Iterable<Appointment> allAppointments = service.getAllAppointments();
            for (Appointment a : allAppointments)
                appointmentsObservableList.add(a);
            listViewAppointments.refresh();
        } catch (NumberFormatException e) {
            showError("Invalid Input", "Please enter valid values");
        } catch (RepositoryException e) {
            showError("Error", e.getMessage());
        }
    }

    @FXML
    void sortByNameButtonHandler(ActionEvent event) {
        List<Dentist> sortedList = service.getSortedDentistsByName();
        dentistsObservableList.clear();
        dentistsObservableList.addAll(sortedList);
    }

    @FXML
    void sortBySpecialtyButtonHandler(ActionEvent event) {
        List<Dentist> sortedList = service.getSortedDentistsBySpecialty();
        dentistsObservableList.clear();
        dentistsObservableList.addAll(sortedList);
    }

    @FXML
    void sortByGradeButtonHandler(ActionEvent event) {
        List<Dentist> sortedList = service.getSortedDentistsByGrade();
        dentistsObservableList.clear();
        dentistsObservableList.addAll(sortedList);
    }

    @FXML
    void sortByIDButtonHandler(ActionEvent event) {
        List<Dentist> sortedList = service.getSortedDentistsByID();
        dentistsObservableList.clear();
        dentistsObservableList.addAll(sortedList);
    }

    @FXML
    void sortByIDButtonHandlerAppointment(ActionEvent event) {
        List<Appointment> sortedList = service.getSortedAppointmentsByTime();
            appointmentsObservableList.clear();
        appointmentsObservableList.addAll(sortedList);
    }

    @FXML
    void filterByTimeButtonHandler(ActionEvent event) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Filter by Time");
        dialog.setHeaderText("Enter the time to filter appointments:");
        dialog.setContentText("Time:");

        Optional<String> result = dialog.showAndWait();

        if (result.isPresent()) {
            try {
                int time = Integer.parseInt(result.get());

                List<Appointment> filteredAppointments = service.filterAppointmentsByTime(time);

                appointmentsObservableList.clear();
                appointmentsObservableList.addAll(filteredAppointments);
            } catch (NumberFormatException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Invalid Input");
                alert.setHeaderText("Error while filtering");
                alert.setContentText("Please enter a valid number for time.");
                alert.showAndWait();
            } catch (RepositoryException e) {
                throw new RuntimeException(e);
            }
        }
    }

    @FXML
    void filterBySpecialtyButtonHandler(ActionEvent event) throws RepositoryException {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Filter by Specialty");
        dialog.setHeaderText("Enter the specialty to filter dentists:");
        dialog.setContentText("Specialty:");

        Optional<String> result = dialog.showAndWait();

        if (result.isPresent()) {
            String specialty = result.get();

            List<Dentist> filteredDentists = service.filterDentistsBySpecialty(specialty);

            dentistsObservableList.clear();
            dentistsObservableList.addAll(filteredDentists);
        }
    }

    @FXML
    void filterByGradeButtonHandler(ActionEvent event) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Filter by Grade");
        dialog.setHeaderText("Enter the grade to filter dentists:");
        dialog.setContentText("Grade:");

        Optional<String> result = dialog.showAndWait();

        if (result.isPresent()) {
            try {
                double grade = Double.parseDouble(result.get());

                List<Dentist> filteredDentists = service.filterDentistsByGrade(grade);

                dentistsObservableList.clear();
                dentistsObservableList.addAll(filteredDentists);
            } catch (NumberFormatException | RepositoryException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Invalid Input");
                alert.setHeaderText("Error while filtering");
                alert.setContentText("Please enter a valid number for grade.");
                alert.showAndWait();
            }
        }
    }

    @FXML
    private void handleUndo(ActionEvent event) {
        try {
            service.undo();
            refreshLists();
        } catch (Exception e) {
            showError("", "There are no actions to undo.");
        }
    }

    @FXML
    private void handleRedo(ActionEvent event) {
        try {
            service.redo();
            refreshLists();
        } catch (Exception e) {
            showError("", "There are no actions to redo.");
        }
    }

    private void refreshLists() throws RepositoryException {
        dentistsObservableList.clear();
        Iterable<Dentist> allDentists = service.getAllDentists();
        for (Dentist d : allDentists)
            dentistsObservableList.add(d);
        listViewDentists.refresh();

        appointmentsObservableList.clear();
        Iterable<Appointment> allAppointments = service.getAllAppointments();
        for (Appointment a : allAppointments)
            appointmentsObservableList.add(a);
        listViewAppointments.refresh();
    }

    private void showError(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setContentText(message);
        alert.showAndWait();
    }
}
