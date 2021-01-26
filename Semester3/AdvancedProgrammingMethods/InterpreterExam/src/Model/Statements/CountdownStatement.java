package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;

public class CountdownStatement implements Statement{
    String variableName;

    public CountdownStatement(String variableName) {
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
        if(! state.getLatchTable().containsKey(variableValue.getValue()))
            throw new InterpreterException("Variable " + variableName + " is not in the latch table");

        Integer latchTableValue = state.getLatchTable().getElementWithKey(variableValue.getValue());
        if(latchTableValue > 0)
            state.getLatchTable().update(variableValue.getValue(), latchTableValue -1);

        state.getOutputConsole().add(new IntValue(state.getProgramStateId().get()));
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        Type variableType = variableTypes.getElementWithKey(variableName);

        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Typechecker: Variable " + variableName + "is not of type int");
        return variableTypes;
    }

    @Override
    public String toString() {
        return "Countdown(" + variableName + ")";
    }
}
