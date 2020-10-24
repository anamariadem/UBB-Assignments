package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Exceptions.TypesDoNotMatch;
import Exceptions.VariableDefinitionException;
import Model.ProgramState;

public class NopStatement implements Statement{

    public NopStatement() {}

    public ProgramState execute(ProgramState state) throws MyException, DivisionByZero, VariableDefinitionException, TypesDoNotMatch{
        return state;
    }

    public String toString(){
        return " ";
    }
}
