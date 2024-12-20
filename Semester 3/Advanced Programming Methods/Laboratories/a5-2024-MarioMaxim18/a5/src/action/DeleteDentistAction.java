package action;

import domain.Dentist;
import domain.Identifiable;
import repository.IRepository;
import repository.RepositoryException;

public class DeleteDentistAction implements IAction {
    private final IRepository<Integer, Identifiable> dentistRepository;
    private final Dentist deletedDentist;

    public DeleteDentistAction(IRepository<Integer, Identifiable> repository, Dentist dentist) {
        this.dentistRepository = repository;
        this.deletedDentist = dentist;
    }

    @Override
    public void executeUndo() throws RepositoryException {
        dentistRepository.addDentist(deletedDentist.getId(), deletedDentist);
    }

    @Override
    public void executeRedo() throws RepositoryException {
        dentistRepository.deleteDentist(deletedDentist.getId());
    }
}
