package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Triplet;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;

import java.util.List;

public class ToyReleaseStatement implements Statement{
    String variableName;

    public ToyReleaseStatement(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        if(! state.getSymbolTable().containsKey(variableName))
            throw new InterpreterException("Variable " + variableName + " was not defined");

        Type variableType = state.getSymbolTable().getElementWithKey(variableName).getType();

        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Variable " + variableName + "is not of type int");

        IntValue variableValue = (IntValue) state.getSymbolTable().getElementWithKey(variableName);
        if(! state.getToySemaphoreTable().containsKey(variableValue.getValue()))
            throw new InterpreterException("Variable " + variableName + " is not in the toy semaphore table " + variableValue.toString());

        Triplet<Integer, List<Integer>, Integer> toySemaphoreTableValue = state.getToySemaphoreTable().getElementWithKey(variableValue.getValue());
        if(toySemaphoreTableValue.getSecond().contains(state.getProgramStateId().get()))
            toySemaphoreTableValue.getSecond().remove(Integer.valueOf(state.getProgramStateId().get()));

        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        return variableTypes;
    }

    @Override
    public String toString() {
        return "ToyRelease(" + variableName + ')';
    }
}
