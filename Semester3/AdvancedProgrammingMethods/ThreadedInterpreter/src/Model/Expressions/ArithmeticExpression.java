package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

public class ArithmeticExpression extends BinaryExpression{
    public ArithmeticExpression(Expression leftSideExpression, Expression rightSideExpression, OPERATION operation) {
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
            case ADDITION: return new IntValue(leftSideValue.getValue() + rightSideValue.getValue());
            case SUBTRACTION: return new IntValue(leftSideValue.getValue() - rightSideValue.getValue());
            case MULTIPLICATION: return new IntValue(leftSideValue.getValue() * rightSideValue.getValue());
            case DIVISION:
                if(rightSideValue.getValue() == 0)
                    throw new InterpreterException("Second operand cannot be 0");
                return new IntValue(leftSideValue.getValue() / rightSideValue.getValue());
            default:
                return new IntValue();
        }
    }

    public Type typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        var leftSideType = leftSideExpression.typeCheck(variableTypes);
        var rightSideType = rightSideExpression.typeCheck(variableTypes);

        if(!leftSideType.equals(new IntType()))
            throw new InterpreterException("Typechecker - Left side:" + leftSideExpression.toString() +" is not of type int");

        if(!rightSideType.equals(new IntType()))
            throw new InterpreterException("Typechecker - Right side:" + rightSideExpression.toString() +" is not of type int");

        return new IntType();
    }
}
