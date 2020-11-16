package Model.Statements;

import Exceptions.*;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFromFileStatement implements Statement{
    Expression expression;
    String variableName;

    public ReadFromFileStatement(Expression expression, String variableName) {
        this.expression = expression;
        this.variableName = variableName;
    }

    public ProgramState execute(ProgramState state)throws InterpreterException{
        var symbolTable = state.getSymbolTable();

        var fileTable = state.getFileTable();

        if(!symbolTable.containsKey(variableName))
            throw new InterpreterException("Variable is nor defined!");

        Value variableValue = symbolTable.getElementWithKey(variableName);
        if(!variableValue.getType().equals(new IntType()))
            throw new InterpreterException("Variable is not of type int");

        Value evaluatedExpression = expression.evaluate(symbolTable, state.getHeap());
        if(!evaluatedExpression.getType().equals(new StringType()))
            throw new InterpreterException("Expression does not evaluate to string type!");

        StringValue fileName = (StringValue) evaluatedExpression;
        if(!fileTable.containsKey(fileName.getValue()))
            throw new InterpreterException("File is not open");

        BufferedReader bufferedReader = fileTable.getElementWithKey(fileName.getValue());

        try {
            String lineRead = bufferedReader.readLine();
            if(lineRead == null)
                lineRead = "0";
            symbolTable.add(variableName, new IntValue(Integer.parseInt(lineRead)));
        }catch (IOException e){
            throw new InterpreterException("An IO exception occured: " + e.getMessage());
        }

        return state;
    }

    @Override
    public String toString() {
        return "READ(" + variableName + ", " + expression.toString() + ")";
    }
}
