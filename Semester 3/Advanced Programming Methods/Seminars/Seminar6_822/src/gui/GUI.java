package gui;

import Repository.*;
import Service.Service;
import domain.Appointment;
import domain.Doctor;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import main.UI;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.Properties;

public class GUI extends Application {
    public IRepository<Integer, Doctor> getRepository() {
        IRepository<Integer, Doctor> doctorsRepository = null;
        FileReader fr = null;
        try {
            fr = new FileReader("settings.properties");
            Properties prop = new Properties();
            prop.load(fr);

            String repositoryType = (String) prop.get("repo_type");
            String repositoryPath = prop.getProperty("repo_path");

            if (repositoryType.equals("text"))
                doctorsRepository = new DoctorsTextFileRepository(repositoryPath);

            if (repositoryType.equals("binary"))
                doctorsRepository = new DoctorsBinaryFileRepository(repositoryPath);

            if (repositoryType.equals("DB"))
                doctorsRepository = new DoctorsDBRepository();

            if (repositoryType.equals("memory"))
                doctorsRepository = new DoctorsRepository();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }

        return doctorsRepository;
    }

    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("view.fxml"));
        IRepository<Integer, Doctor> repo = getRepository();
        Service service = new Service(repo, null, null);
        Controller controller = new Controller(service);
        loader.setController(controller);
        Scene scene = new Scene(loader.load(), 600, 400);
        stage.setTitle("GUI for Doctors App");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
