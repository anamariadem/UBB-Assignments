package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;

import java.util.concurrent.atomic.AtomicInteger;

public class NewLockStatement implements Statement{
    String variableName;

    public NewLockStatement(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        if(! state.getSymbolTable().containsKey(variableName))
            throw new InterpreterException("Variable " + variableName + " was not defined");

        Type variableType = state.getSymbolTable().getElementWithKey(variableName).getType();

        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Variable " + variableName + "is not of type int");

        AtomicInteger address = state.getLockTable().allocate();
        state.getLockTable().add(address.get(), -1);
        state.getSymbolTable().update(variableName, new IntValue(address.get()));
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
        return "newLock(" + variableName + ")";
    }
}
