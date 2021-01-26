package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Triplet;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import javafx.util.Pair;

import java.util.List;

public class CountReleaseStatement implements Statement{
    String variableName;

    public CountReleaseStatement(String variableName) {
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
        if(! state.getCountSemaphoreTable().containsKey(variableValue.getValue()))
            throw new InterpreterException("Variable " + variableName + " is not in the count semaphore table " + variableValue.toString());

        Pair<Integer, List<Integer>> countSemaphoreTableValue = state.getCountSemaphoreTable().getElementWithKey(variableValue.getValue());
        if(countSemaphoreTableValue.getValue().contains(state.getProgramStateId().get()))
            countSemaphoreTableValue.getValue().remove(Integer.valueOf(state.getProgramStateId().get()));

        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        Type variableType = variableTypes.getElementWithKey(variableName);

        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Typechecker: Variable " + variableName + "is not of type int");
        return variableTypes;
    }
}
