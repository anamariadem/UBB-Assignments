package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.util.concurrent.atomic.AtomicInteger;

public class NewLatchStatement implements Statement{
    String variableName;
    Expression expression;

    public NewLatchStatement(String variableName, Expression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        Value expressionValue = expression.evaluate(state.getSymbolTable(), state.getHeap());
        if(! expressionValue.getType().equals(new IntType()))
            throw new InterpreterException("Expression " + expression.toString() + " is not of type int");

        if(! state.getSymbolTable().containsKey(variableName))
            throw new InterpreterException("Variable " + variableName + " was not defined");

        Type variableType = state.getSymbolTable().getElementWithKey(variableName).getType();

        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Variable " + variableName + "is not of type int");

        AtomicInteger address = state.getLatchTable().allocate();
        state.getLatchTable().add(address.get(), ((IntValue) expressionValue).getValue());
        state.getSymbolTable().update(variableName, new IntValue(address.get()));
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        Type variableType = variableTypes.getElementWithKey(variableName);
        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Typechecker: Variable " + variableName + " is not of type int");

        Type expressionType = expression.typeCheck(variableTypes);
        if(! expressionType.equals(new IntType()))
            throw new InterpreterException("Typechecker: Expression " + expression.toString() + " is not of type int");

        return variableTypes;
    }

    @Override
    public String toString() {
        return "newLatch(" + variableName + ", " + expression.toString() + ")";
    }
}
