package Model.Expressions;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyHeapInterface;
import Model.Types.Type;
import Model.Values.Value;

public interface Expression {
    Value evaluate(MyDictionaryInterface<String, Value> table, MyHeapInterface<Value> heap) throws InterpreterException;
    Type typeCheck (MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException;
}
