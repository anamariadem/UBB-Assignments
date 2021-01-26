package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.Type;

public class SleepStatement implements Statement{
    Integer number;

    public SleepStatement(Integer number) {
        this.number = number;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        if(number == 0)
            return null;
        state.getExecutionStack().push(new SleepStatement(number - 1));
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        return variableTypes;
    }

    @Override
    public String toString() {
        return "Sleep(" + number + ')';
    }
}
