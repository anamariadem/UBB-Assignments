package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyDictionaryInterface;
import Model.Values.Value;

public class VariableExpression implements Expression{
    String variable;

    public VariableExpression(String variable){
        this.variable = variable;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table) throws MyException{
        return table.getElementWithKey(this.variable);
    }

    public String toString(){
        return variable;
    }
}
