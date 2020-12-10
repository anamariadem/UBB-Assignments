package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;

public class ReadHeapExpression implements Expression{
    Expression expression;

    public ReadHeapExpression(Expression expression) {
        this.expression = expression;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException {
        Value evaluatedExpression = expression.evaluate(table, heap);

        if(! (evaluatedExpression instanceof ReferenceValue))
            throw new InterpreterException("Expression " + expression.toString() + " was not evaluated to Ref Value");

        var address = ((ReferenceValue) evaluatedExpression).getAddress();

        if(!heap.containsKey(address))
            throw new InterpreterException("Address does not exist in the heap!");

        return heap.getElementWithKey(address);
    }

    public Type typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        Type expressionType = expression.typeCheck(variableTypes);

        if(!(expressionType instanceof ReferenceType))
            throw new InterpreterException("Typechecker - Expression " + expression.toString() + " does not have a Reference type");

        ReferenceType expressionReferenceType = (ReferenceType) expressionType;
        return expressionReferenceType.getInner();
    }

    public String toString() {
        return "readHeap(" + expression.toString() + ")";
    }
}
