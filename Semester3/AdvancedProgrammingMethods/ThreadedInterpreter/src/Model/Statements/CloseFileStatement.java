package Model.Statements;

import Exceptions.*;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseFileStatement implements Statement{
    Expression expression;

    public CloseFileStatement(Expression expression) {
        this.expression = expression;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException{
        MyDictionaryInterface<String, BufferedReader> fileTable = state.getFileTable();

        Value evaluatedExpression = expression.evaluate(state.getSymbolTable(), state.getHeap());
        if(!evaluatedExpression.getType().equals(new StringType()))
            throw new InterpreterException("Expression " + expression.toString() + " was not evaluated to string!");

        StringValue fileName = (StringValue) evaluatedExpression;
        if(!fileTable.containsKey(fileName.getValue()))
            throw new InterpreterException("File" + fileName + " does not exist!");

        try {
            BufferedReader bufferedReader = fileTable.getElementWithKey(fileName.getValue());
            bufferedReader.close();
            fileTable.remove(fileName.getValue());
        }catch (IOException exception){
            throw new InterpreterException("An IO exception occured: " + exception.getMessage());
        }

        return null;
    }

    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        var expressionType = expression.typeCheck(variableTypes);

        if(!expressionType.equals(new StringType()))
            throw new InterpreterException("Typechecker - Expression: " + expression.toString() + " is not of type String");

        return variableTypes;
    }

    public String toString(){
        return "close(" + expression.toString() + ")";
    }
}
