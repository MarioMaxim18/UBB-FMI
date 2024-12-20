package action;

import domain.Appointment;
import domain.Identifiable;
import repository.IRepository;
import repository.RepositoryException;

public class DeleteAppointmentAction implements IAction {
    private final IRepository<Integer, Identifiable> appointmentRepository;
    private final Appointment deletedAppointment;

    public DeleteAppointmentAction(IRepository<Integer, Identifiable> repository, Appointment appointment) {
        this.appointmentRepository = repository;
        this.deletedAppointment = appointment;
    }

    @Override
    public void executeUndo() throws RepositoryException {
        appointmentRepository.addAppointment(deletedAppointment.getId(), deletedAppointment);
    }

    @Override
    public void executeRedo() throws RepositoryException {
        appointmentRepository.deleteAppointment(deletedAppointment.getId());
    }
}
