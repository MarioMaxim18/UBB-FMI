package gui;

import domain.Appointment;
import repository.*;
import service.Service;
import domain.Dentist;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class GUI extends Application {
    public IRepository<Integer, Dentist> getRepository() {
        IRepository<Integer, Dentist> dentistRepository = null;
        IRepository<Integer, Appointment> appointmentRepository = null;

        FileReader fr = null;
        try {
            fr = new FileReader("settings.properties");
            Properties prop = new Properties();
            prop.load(fr);

            String repositoryType = (String) prop.get("repo_type");
            String repositoryPath = prop.getProperty("repo_path");

            if (repositoryType.equals("text"))
                dentistRepository = new DentistTextFileRepository(repositoryPath);

            if (repositoryType.equals("binary"))
                dentistRepository = new DentistBinaryFileRepository(repositoryPath);

            if (repositoryType.equals("DB"))
                    dentistRepository = new DentistDBRepository();

            if (repositoryType.equals("memory"))
                dentistRepository = new MemoryRepository<>();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }

        return dentistRepository;
    }

    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("view.fxml"));
        IRepository<Integer, Dentist> dentistRepo = getRepository();
        IRepository<Integer, Appointment> appointmentRepo =  new AppointmentDBRepository((DentistDBRepository) dentistRepo);
        Service service = new Service(dentistRepo, appointmentRepo);
        Controller controller = new Controller(service);
        loader.setController(controller);
        Scene scene = new Scene(loader.load(), 1000, 600);
        stage.setTitle("GUI");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
