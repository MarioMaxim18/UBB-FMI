package action;

import domain.Dentist;
import domain.Identifiable;
import repository.IRepository;
import repository.RepositoryException;

public class UpdateDentistAction implements IAction {
    private final IRepository<Integer, Identifiable> dentistRepository;
    private final Dentist oldDentist;
    private final Dentist newDentist;

    public UpdateDentistAction(IRepository<Integer, Identifiable> repository, Dentist oldDentist, Dentist newDentist) {
        this.dentistRepository = repository;
        this.oldDentist = oldDentist;
        this.newDentist = newDentist;
    }

    @Override
    public void executeUndo() throws RepositoryException {
        dentistRepository.modifyDentist(oldDentist.getId(), oldDentist);
    }

    @Override
    public void executeRedo() throws RepositoryException {
        dentistRepository.modifyDentist(newDentist.getId(), newDentist);
    }
}
