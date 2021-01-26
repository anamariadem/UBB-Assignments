package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public class NewCountSemaphoreStatement implements Statement{
    String variableName;
    Expression expression;

    public NewCountSemaphoreStatement(String variableName, Expression expression) {
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

        IntValue expressionIntValue = (IntValue) expressionValue;
        AtomicInteger address = state.getCountSemaphoreTable().allocate();
        state.getCountSemaphoreTable().add(address.get(),
                new Pair<>(expressionIntValue.getValue(), new ArrayList<>()));

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
        return "NewCountSemaphore (" + variableName + ", " + expression.toString() + ')';
    }
}
