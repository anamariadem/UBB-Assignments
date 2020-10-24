package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Exceptions.TypesDoNotMatch;
import Exceptions.VariableDefinitionException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
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

    public ProgramState execute(ProgramState state) throws MyException, DivisionByZero, VariableDefinitionException, TypesDoNotMatch{
        MyDictionaryInterface<String, Value> symbolTable = state.getSymbolTable();

        if(symbolTable.isVariableDefined(this.variableName))
            throw new VariableDefinitionException("Variable is already defined");
        else {
            if(this.variableType.equals(new IntType()))
                symbolTable.add(this.variableName, new IntValue());
            else if(this.variableType.equals(new BoolType())){
                symbolTable.add(this.variableName, new BoolValue());
            }else throw new VariableDefinitionException("Invalid type");
        }

        state.setSymbolTable(symbolTable);
        return state;
    }

    public String toString(){
        return this.variableType.toString() + " " + this.variableName;
    }
}
