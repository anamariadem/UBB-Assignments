package Repository;

import Model.ProgramState;

public interface RepositoryInterface {
    ProgramState getCurrentProgramState();
    void addProgramState(ProgramState state);
}
