package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Types.Type;
import Model.Values.Value;

public class ValueExpression implements Expression {
    Value value;

    public ValueExpression(Value value){
        this.value = value;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException {
        return this.value;
    }

    public Type typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        return value.getType();
    }

    public String toString(){
        return value.toString();
    }
}
