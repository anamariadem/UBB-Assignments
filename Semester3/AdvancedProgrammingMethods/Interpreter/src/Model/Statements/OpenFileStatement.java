package Model.Statements;

import Exceptions.*;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.StringType;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenFileStatement implements Statement{
    Expression expression;

    public OpenFileStatement(Expression expression) {
        this.expression = expression;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException{
        MyDictionaryInterface<String, BufferedReader> fileTable = state.getFileTable();

        Value evaluatedExpression = expression.evaluate(state.getSymbolTable(), state.getHeap());
        if(!evaluatedExpression.getType().equals(new StringType()))
            throw new InterpreterException("Expression " + expression.toString() + " was not evaluated to string!");

        StringValue fileName = (StringValue) evaluatedExpression;
        if(fileTable.containsKey(fileName.getValue()))
            throw new InterpreterException("File" + fileName + " is open!");

        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName.getValue()));
            fileTable.add(fileName.getValue(), bufferedReader);
        }catch (IOException exception){
            throw new InterpreterException("An IO exception occured: " + exception.getMessage());
        }

        return state;
    }

    public String toString(){
        return "open(" + expression.toString() + ")";
    }
}
