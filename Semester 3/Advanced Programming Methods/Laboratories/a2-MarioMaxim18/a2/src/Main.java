import UI.UI;
import domain.Identifiable;
import repository.IRepository;
import repository.MemoryRepository;
import service.Service;

public class Main {
    public static  void main(String[] args) {
        IRepository<Integer, Identifiable> repo = new MemoryRepository<>();
        Service service = new Service(repo);
        UI ui = new UI(service);
        ui.run();
    }
    // isPrime_primeNumber_returnsTrue() { assert(isPrime(2) == true);}
    // isPrime_zero_returnsFalse();
    // isPrime_letter_throwsException();
    //
    // FakeRepo fake = new FakeRepo();
    // Service serviceToTest = new Service(fake);
    // assert serviceToTest.Add(something) == true;
}
    