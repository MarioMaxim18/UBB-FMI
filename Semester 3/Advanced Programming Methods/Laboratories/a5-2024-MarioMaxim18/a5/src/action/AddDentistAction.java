package action;

import domain.Dentist;
import domain.Identifiable;
import repository.IRepository;
import repository.RepositoryException;

public class AddDentistAction implements IAction {
    private final IRepository<Integer, Identifiable> dentistRepository;
    private final Dentist addedDentist;

    public AddDentistAction(IRepository<Integer, Identifiable> repository, Dentist dentist) {
        this.dentistRepository = repository;
        this.addedDentist = dentist;
    }

    @Override
    public void executeUndo() throws RepositoryException {
        dentistRepository.deleteDentist(addedDentist.getId());
    }

    @Override
    public void executeRedo() throws RepositoryException {
        dentistRepository.addDentist(addedDentist.getId(), addedDentist);
    }
}
