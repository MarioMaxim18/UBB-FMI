package action;

import domain.Appointment;
import domain.Identifiable;
import repository.IRepository;
import repository.RepositoryException;

public class UpdateAppointmentAction implements IAction {
    private final IRepository<Integer, Identifiable> appointmentRepository;
    private final Appointment oldAppointment;
    private final Appointment newAppointment;

    public UpdateAppointmentAction(IRepository<Integer, Identifiable> repository, Appointment oldAppointment, Appointment newAppointment) {
        this.appointmentRepository = repository;
        this.oldAppointment = oldAppointment;
        this.newAppointment = newAppointment;
    }

    @Override
    public void executeUndo() throws RepositoryException {
        appointmentRepository.modifyAppointment(oldAppointment.getId(), oldAppointment);
    }

    @Override
    public void executeRedo() throws RepositoryException {
        appointmentRepository.modifyAppointment(newAppointment.getId(), newAppointment);
    }
}
