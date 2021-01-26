package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Triplet;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class NewToySemaphoreStatement implements Statement{
    String variableName;
    Expression firstExpression;
    Expression secondExpression;

    public NewToySemaphoreStatement(String variableName, Expression firstExpression, Expression secondExpression) {
        this.variableName = variableName;
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        Value firstExpressionValue = firstExpression.evaluate(state.getSymbolTable(), state.getHeap());
        Value secondExpressionValue = secondExpression.evaluate(state.getSymbolTable(), state.getHeap());

        if(! firstExpressionValue.getType().equals(new IntType()))
            throw new InterpreterException("The first expression: " + firstExpression.toString() + " was not evaluated to int");

        if(! secondExpressionValue.getType().equals(new IntType()))
            throw new InterpreterException("The second expression: " + secondExpression.toString() + " was not evaluated to int");

        if(! state.getSymbolTable().containsKey(variableName))
            throw new InterpreterException("Variable " + variableName + " was not defined");

        Type variableType = state.getSymbolTable().getElementWithKey(variableName).getType();

        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Variable " + variableName + "is not of type int");

        IntValue firstExpressionIntValue = (IntValue) firstExpressionValue;
        IntValue secondExpressionIntValue = (IntValue) secondExpressionValue;

        AtomicInteger address = state.getToySemaphoreTable().allocate();
        state.getToySemaphoreTable().add(address.get(), new Triplet<>(firstExpressionIntValue.getValue(),
                new ArrayList<>(), secondExpressionIntValue.getValue()));

        state.getSymbolTable().update(variableName, new IntValue(address.get()));
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        return variableTypes;
    }

    @Override
    public String toString() {
        return "NewToySemaphore(" + variableName + ", " + firstExpression.toString() +
                ", " + secondExpression.toString() + ')';
    }
}
