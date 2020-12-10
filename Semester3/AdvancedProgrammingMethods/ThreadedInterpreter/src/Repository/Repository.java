package Repository;

import Exceptions.InterpreterException;
import Model.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements RepositoryInterface{
    List<ProgramState> programStates;
    String logFilePath;

    public Repository(String logFilePath){
        this.programStates = new ArrayList<>();
        this.logFilePath = logFilePath;
    }

    /*public ProgramState getCurrentProgramState(){
        //ProgramState currentProgramState = this.programStates.get(0);
        //this.programStates.remove(0);
        return this.programStates.get(0);
    }*/

    public List<ProgramState> getProgramStatesList() {
        return programStates;
    }

    @Override
    public void setProgramStatesList(List<ProgramState> programStates) {
        this.programStates = programStates;
    }

    public void addProgramState(ProgramState state){
        this.programStates.add(state);
    }


    public void logProgramStateExecution(ProgramState state) throws InterpreterException {
        PrintWriter logFile;
        try {
            logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
        }catch (IOException exception){
            throw new InterpreterException("An IO exception occured:" + exception.getMessage());
        }

        logFile.println(state.toString());
        logFile.close();
    }
}
