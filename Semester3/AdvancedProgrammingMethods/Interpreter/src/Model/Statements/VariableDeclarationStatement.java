package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.InterpreterException;
import Exceptions.TypesDoNotMatch;
import Exceptions.VariableDefinitionException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.*;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Value;

public class VariableDeclarationStatement implements Statement{
    String variableName;
    Type variableType;

    public VariableDeclarationStatement(String variableName, Type variableType){
        this.variableName = variableName;
        this.variableType = variableType;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException{
        MyDictionaryInterface<String, Value> symbolTable = state.getSymbolTable();

        if(symbolTable.containsKey(this.variableName))
            throw new InterpreterException("Variable is already defined");

        symbolTable.add(this.variableName, variableType.getDefault());
        return state;
    }

    public String toString(){
        return this.variableType.toString() + " " + this.variableName;
    }
}
