package Controller;

import Exceptions.*;
import Model.ADTs.MyStackInterface;
import Model.ProgramState;
import Model.Statements.Statement;
import Repository.RepositoryInterface;

public class Controller {
    RepositoryInterface repository;

    public Controller(RepositoryInterface repository){
        this.repository = repository;
    }

    public String stateToString(ProgramState state){
        return state.toString();
    }

    public void addProgramState(ProgramState programState){
        this.repository.addProgramState(programState);
    }

    public ProgramState oneStep(ProgramState state) throws EmptyCollectionException, InvalidDataType, VariableDefinitionException, TypesDoNotMatch, DivisionByZero, MyException {
        MyStackInterface<Statement> stack = state.getExecutionStack();
        if(stack.isEmpty()){
            throw new EmptyCollectionException("Stack is empty");
        }
        Statement currentState = stack.pop();
        return currentState.execute(state);
    }

    public void allSteps(){
        ProgramState programState = repository.getCurrentProgramState();
        System.out.println(programState.toString());

        while (!programState.getExecutionStack().isEmpty()){
            try {
                oneStep(programState);
                System.out.println(programState.toString());
            }catch (Exception exception){
                System.out.println(exception.getMessage());
            }
        }
    }
}
