package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Value;

public class RelationalExpression extends BinaryExpression {
    public RelationalExpression(Expression leftSideExpression, Expression rightSideExpression, OPERATION operation) {
        super(leftSideExpression, rightSideExpression, operation);
    }

    public static IntValue getValue(MyDictionaryInterface<String, Value> table, Expression expression, MyHeapInterface<Value> heap) throws InterpreterException {
        Value valueAfterEvaluation = expression.evaluate(table, heap);
        if(valueAfterEvaluation instanceof IntValue)
            return (IntValue)valueAfterEvaluation;
        throw new InterpreterException("Operand is not integer");
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException{
        IntValue leftSideValue = getValue(table, this.leftSideExpression, heap);
        IntValue rightSideValue = getValue(table, this.rightSideExpression, heap);

        switch (operation){
            case LESS: return new BoolValue(leftSideValue.getValue() < rightSideValue.getValue());
            case LESS_OR_EQUAL: return new BoolValue(leftSideValue.getValue() <= rightSideValue.getValue());
            case MORE: return new BoolValue(leftSideValue.getValue() > rightSideValue.getValue());
            case MORE_OR_EQUAL: return new BoolValue(leftSideValue.getValue() >= rightSideValue.getValue());
            case EQUAL: return new BoolValue(leftSideValue.getValue() == rightSideValue.getValue());
            case NOT_EQUAL: return new BoolValue(leftSideValue.getValue() != rightSideValue.getValue());
            default: return new BoolValue();
        }
    }

    public Type typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        var leftSideType = leftSideExpression.typeCheck(variableTypes);
        var rightSideType = rightSideExpression.typeCheck(variableTypes);

        if(!leftSideType.equals(new IntType()))
            throw new InterpreterException("Typechecker - Left side:" + leftSideExpression.toString() +" is not of type int");

        if(!rightSideType.equals(new IntType()))
            throw new InterpreterException("Typechecker - Right side:" + rightSideExpression.toString() +" is not of type int");

        return new BoolType();
    }
}
