package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.InterpreterException;
import Exceptions.TypesDoNotMatch;
import Exceptions.VariableDefinitionException;
import Model.ProgramState;

public class NopStatement implements Statement{

    public NopStatement() {}

    public ProgramState execute(ProgramState state) throws InterpreterException{
        return state;
    }

    public String toString(){
        return " ";
    }
}
