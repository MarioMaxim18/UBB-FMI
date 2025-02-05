import Repository.*;
import Service.Service;
import domain.Doctor;
import domain.Entity;
import domain.Patient;
import Repository.FilteredRepository;
import filter.FilterDoctorsBySpecialty;

import javax.print.Doc;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.Properties;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void printElems(Repository<Integer, Doctor> r){
        for(Doctor doctor: r.getAll())
            System.out.println(doctor);
    }

    public static void main(String[] args) {
        IRepository<Integer, Doctor> doctorsRepository = null;

        // read the properties file
        FileReader fr = null;
        try {
            fr = new FileReader("settings.properties");
            Properties prop = new Properties();
            prop.load(fr);

            String repositoryType = (String) prop.get("repo_type");
            String repositoryPath = prop.getProperty("repo_path");

            if (repositoryType.equals("text"))
                doctorsRepository = new DoctorsTextFileRepository(repositoryPath);

            if (repositoryType.equals("memory"))
                doctorsRepository = new DoctorsRepository();

            for (Doctor d: doctorsRepository.getAll())
                System.out.println(d);

            Service serv = new Service(doctorsRepository);

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }

    }
}