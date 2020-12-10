package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.Type;

public class NopStatement implements Statement {

    public NopStatement() {}

    public ProgramState execute(ProgramState state) throws InterpreterException{
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        return variableTypes;
    }

    public String toString(){
        return " ";
    }
}
