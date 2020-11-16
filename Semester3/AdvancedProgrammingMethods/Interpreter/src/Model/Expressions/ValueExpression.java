package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Values.Value;

public class ValueExpression implements Expression{
    Value value;

    public ValueExpression(Value value){
        this.value = value;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException {
        return this.value;
    }

    public String toString(){
        return value.toString();
    }
}
