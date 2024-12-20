package action;

import domain.Appointment;
import domain.Identifiable;
import repository.IRepository;
import repository.RepositoryException;

public class AddAppointmentAction  implements IAction {
    private final IRepository<Integer, Identifiable> appointmentRepository;
    private final Appointment addedAppointment;

    public AddAppointmentAction(IRepository<Integer, Identifiable> repository, Appointment appointment) {
        this.appointmentRepository = repository;
        this.addedAppointment = appointment;
    }

    @Override
    public void executeUndo() throws RepositoryException {
        appointmentRepository.deleteAppointment(addedAppointment.getId());
    }

    @Override
    public void executeRedo() throws RepositoryException {
        appointmentRepository.addAppointment(addedAppointment.getId(), addedAppointment);
    }
}

