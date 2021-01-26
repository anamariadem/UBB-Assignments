package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.Type;
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
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        variableTypes.add(variableName, variableType);
        return variableTypes;
    }

    public String toString(){
        return this.variableType.toString() + " " + this.variableName;
    }
}
