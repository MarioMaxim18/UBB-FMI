package repository;

import domain.Dentist;

import java.io.*;
import java.util.HashMap;

public class DentistBinaryFileRepository extends FileRepository<Dentist> {
    public DentistBinaryFileRepository(String filename) throws RepositoryException{
        super(filename);
    }

    @Override
    protected void readFromFile() throws RepositoryException {
        try(ObjectInputStream objectInputStream=new ObjectInputStream(new FileInputStream(filename))){
            this.dentists=(HashMap<Integer, Dentist>) objectInputStream.readObject();
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
            objectOutputStream.writeObject(this.dentists);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
