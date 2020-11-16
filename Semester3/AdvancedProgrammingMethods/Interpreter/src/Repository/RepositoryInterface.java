package Repository;

import Exceptions.InterpreterException;
import Model.ProgramState;

public interface RepositoryInterface {
    ProgramState getCurrentProgramState();
    void addProgramState(ProgramState state);
    void logProgramStateExecution(ProgramState state) throws InterpreterException;
}
