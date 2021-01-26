package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;

public class NotExpression implements Expression{
    Expression expression;

    public NotExpression(Expression expression) {
        this.expression = expression;
    }

    public static BoolValue getValue(MyDictionaryInterface<String, Value> table, Expression expression, MyHeapInterface<Value> heap) throws InterpreterException{
        Value valueAfterEvaluation = expression.evaluate(table, heap);
        if(valueAfterEvaluation instanceof BoolValue)
            return (BoolValue)valueAfterEvaluation;
        throw new InterpreterException("Operand is not bool");
    }

    @Override
    public Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException {
        BoolValue expressionValue = getValue(table, expression, heap);
        return new BoolValue(!expressionValue.getValue());
    }

    @Override
    public Type typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        var expressionType = expression.typeCheck(variableTypes);
        if(!expressionType.equals(new BoolType()))
            throw new InterpreterException("Typechecker - Expression:" + expression.toString() +" is not of type bool");

        return new BoolType();
    }

    @Override
    public String toString() {
        return "Not (" + expression.toString() + ")";
    }
}
