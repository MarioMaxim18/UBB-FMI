package main;

import UI.UI;
import domain.Dentist;
import repository.*;
import repository.DentistBinaryFileRepository;
import repository.DentistTextFileRepository;
import service.Service;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Main {
    public static void main(String[] args) {
//        IRepository<Integer, Dentist> repo = null;
//
//        FileReader fileToRead = null;
//        try {
//            fileToRead = new FileReader("settings.properties");
//            Properties prop = new Properties();
//            prop.load(fileToRead);
//
//            String repositoryType = (String) prop.get("repo_type");
//            String repositoryPath = prop.getProperty("repo_path");
//
//            if (repositoryType.equals("text"))
//                repo = new DentistTextFileRepository(repositoryPath);
//
//            if (repositoryType.equals("binary"))
//                repo = new DentistBinaryFileRepository(repositoryPath);
//
//            if (repositoryType.equals("DB"))
//                repo = new DentistDBRepository();
//
//            if (repositoryType.equals("memory"))
//                repo = new MemoryRepository<>();
//
//            Service service = new Service(repo);
//            UI ui = new UI(service);
//            ui.run();
//
//        } catch (FileNotFoundException e) {
//            throw new RuntimeException(e);
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        } catch (RepositoryException e) {
//            throw new RuntimeException(e);
//        }
    }
}
    