package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Values.BoolValue;
import Model.Values.Value;

public class LogicalExpression extends BinaryExpression{
    public LogicalExpression(Expression leftSideExpression, Expression rightSideExpression, OPERATION operation) {
        super(leftSideExpression, rightSideExpression, operation);
    }

    public static BoolValue getValue(MyDictionaryInterface<String, Value> table, Expression expression, MyHeapInterface<Value> heap) throws InterpreterException{
        Value valueAfterEvaluation = expression.evaluate(table, heap);
        if(valueAfterEvaluation instanceof BoolValue)
            return (BoolValue)valueAfterEvaluation;
        throw new InterpreterException("Operand is not bool");
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException{
        BoolValue leftSideValue = getValue(table, this.leftSideExpression, heap);
        BoolValue rightSideValue = getValue(table, this.rightSideExpression, heap);

        switch (operation){
            case AND: return new BoolValue(leftSideValue.getValue() && rightSideValue.getValue());
            case OR: return new BoolValue(leftSideValue.getValue() || rightSideValue.getValue());
            default: return new BoolValue();
        }
    }

}
