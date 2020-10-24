package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyDictionaryInterface;
import Model.Values.Value;

public class ValueExpression implements Expression{
    Value value;

    public ValueExpression(Value value){
        this.value = value;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table) throws MyException{
        return this.value;
    }

    public String toString(){
        return value.toString();
    }
}
