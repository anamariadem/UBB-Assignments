package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.util.concurrent.atomic.AtomicInteger;

public class LockStatement implements Statement{
    String variableName;

    public LockStatement(String variableName) {
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

        Integer lockTableValue = state.getLockTable().getElementWithKey(variableValue.getValue());
        if(lockTableValue == -1){
            state.getLockTable().update(variableValue.getValue(), state.getProgramStateId().get());
        }else {
            state.getExecutionStack().push(this);
        }

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
        return "lock(" + variableName + ")";
    }
}
