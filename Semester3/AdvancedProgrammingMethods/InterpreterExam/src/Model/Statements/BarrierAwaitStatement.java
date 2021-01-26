package Model.Statements;


import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import javafx.util.Pair;

import java.util.List;

public class BarrierAwaitStatement implements Statement{
    String variableName;

    public BarrierAwaitStatement(String variableName) {
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
        if(! state.getBarrierTable().containsKey(variableValue.getValue()))
            throw new InterpreterException("Variable " + variableName + " is not in the barrier table " + variableValue.toString());

        Pair<Integer, List<Integer>> barrierTableValue =
                state.getBarrierTable().getElementWithKey(variableValue.getValue());

        if(barrierTableValue.getKey() > barrierTableValue.getValue().size()){
            if(! barrierTableValue.getValue().contains(state.getProgramStateId().get()))
                barrierTableValue.getValue().add(state.getProgramStateId().get());
            state.getExecutionStack().push(this);
        }
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        return variableTypes;
    }

    @Override
    public String toString() {
        return "BarrierAwait(" + variableName + ')';
    }
}
