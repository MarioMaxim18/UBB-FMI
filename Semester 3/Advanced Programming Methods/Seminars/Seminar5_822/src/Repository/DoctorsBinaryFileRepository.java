package Repository;

import domain.Doctor;

import java.io.*;
import java.util.HashMap;

public class DoctorsBinaryFileRepository extends FileRepository<Integer, Doctor> {
    public DoctorsBinaryFileRepository(String filename) throws RepositoryException{
        super(filename);
    }

    @Override
    protected void readFromFile() throws RepositoryException {
        try(ObjectInputStream objectInputStream=new ObjectInputStream(new FileInputStream(filename))){
            this.entities=(HashMap<Integer, Doctor>) objectInputStream.readObject();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void writeToFile() {
        try(ObjectOutputStream objectOutputStream=new ObjectOutputStream(new FileOutputStream(filename))){
            objectOutputStream.writeObject(this.entities);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
