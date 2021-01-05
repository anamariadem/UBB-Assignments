package Repository;

import Exceptions.InterpreterException;
import Model.ProgramState;

import java.util.List;

public interface RepositoryInterface {
    //ProgramState getCurrentProgramState();
    void addProgramState(ProgramState state);
    void logProgramStateExecution(ProgramState state) throws InterpreterException;
    List<ProgramState> getProgramStatesList();
    void setProgramStatesList(List<ProgramState> programStates);
}
