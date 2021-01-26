package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;

import java.util.concurrent.atomic.AtomicInteger;

public class UnlockStatement implements Statement{
    String variableName;

    public UnlockStatement(String variableName) {
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
        if(! state.getLockTable().containsKey(variableValue.getValue()))
            throw new InterpreterException("Variable " + variableName + " is not in the lock table " + variableValue.toString());

        if(state.getLockTable().getElementWithKey(variableValue.getValue())
                == state.getProgramStateId().get())
            state.getLockTable().update(variableValue.getValue(), -1);

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
        return "Unlock(" + variableName + ")";
    }
}
