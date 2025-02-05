package Repository;

import domain.Doctor;

import java.io.*;

public class DoctorsTextFileRepository extends FileRepository<Integer, Doctor> {
    public DoctorsTextFileRepository(String filename) throws RepositoryException {
        super(filename);
    }

    @Override
    protected void readFromFile() throws RepositoryException {
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                if (data.length != 4)
                    continue;
                Integer id = Integer.parseInt(data[0]);
                String name = data[1];
                String specialty = data[2];
                Double grade = Double.parseDouble(data[3]);
                Doctor d = new Doctor(id, name, specialty, grade);
                super.add(id, d);
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
            for (Doctor d: super.getAll())
            {
                bw.write(d.getID() + "," + d.getName() + "," + d.getSpecialty() + "," + d.getGrade() + "\n");
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
