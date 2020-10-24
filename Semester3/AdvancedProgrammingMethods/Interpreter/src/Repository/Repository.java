package Repository;

import Model.ProgramState;

import java.util.ArrayList;

public class Repository implements RepositoryInterface{
    ArrayList<ProgramState> programStates;

    public Repository(){
        this.programStates = new ArrayList<>();
    }

    public ProgramState getCurrentProgramState(){
        ProgramState currentProgramState = this.programStates.get(0);
        this.programStates.remove(0);
        return currentProgramState;
    }
    public void addProgramState(ProgramState state){
        this.programStates.add(state);
    }
}
