package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Values.Value;

public class VariableExpression implements Expression{
    String variable;

    public VariableExpression(String variable){
        this.variable = variable;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException {
        return table.getElementWithKey(this.variable);
    }

    public String toString(){
        return variable;
    }
}
