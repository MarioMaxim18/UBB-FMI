package repository;

import domain.Dentist;

import java.io.*;
import java.util.HashMap;

public class DentistTextFileRepository  extends FileRepository<Dentist> {
    private static final int EXPECTED_FIELDS_COUNT = 4;

    public DentistTextFileRepository(String filename) throws RepositoryException {
        super(filename);
    }

    @Override
    protected void readFromFile() throws RepositoryException {
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                if (data.length !=  EXPECTED_FIELDS_COUNT)
                    continue;
                Integer id = Integer.parseInt(data[0]);
                String name = data[1];
                String specialty = data[2];
                Double grade = Double.parseDouble(data[3]);
                Dentist dentist = new Dentist(id, name, specialty, grade);
                super.addDentist(id, dentist);
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void writeToFile() {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(this.filename)))
        {
            for (Dentist dentist: super.getAllDentists())
            {
                bw.write(dentist.getId() + "," + dentist.getName() + "," + dentist.getSpecialty() + "," + dentist.getGrade() + "\n");
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
