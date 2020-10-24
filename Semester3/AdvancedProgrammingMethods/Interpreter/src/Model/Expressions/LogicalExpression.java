package Model.Expressions;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyDictionaryInterface;
import Model.Values.BoolValue;
import Model.Values.Value;
import Model.Types.BoolType;

public class LogicalExpression implements Expression{
    Expression expression1;
    Expression expression2;
    int operation; //1-and, 2-or

    public LogicalExpression(Expression expression1, Expression expression2, int operation){
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operation = operation;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table) throws MyException, DivisionByZero {
        Value firstValueAfterEvaluation;
        Value secondValueAfterEvaluation;

        firstValueAfterEvaluation = this.expression1.evaluate(table);
        if(firstValueAfterEvaluation.getType().equals(new BoolType())){
            secondValueAfterEvaluation = this.expression2.evaluate(table);
            if(secondValueAfterEvaluation.getType().equals(new BoolType())){
                BoolValue firstValueAsBool = (BoolValue)firstValueAfterEvaluation;
                BoolValue secondValueAsBool = (BoolValue)secondValueAfterEvaluation;
                boolean firstTerm = firstValueAsBool.getValue();
                boolean secondTerm = secondValueAsBool.getValue();
                switch (this.operation){
                    case 1: return new BoolValue(firstTerm && secondTerm);
                    case 2: return new BoolValue(firstTerm || secondTerm);
                    default: throw new MyException("Invalid operation");
                }
            }
            else {
                throw new MyException("Second operand is not boolean");
            }
        }
        else {
            throw new MyException("First operand is not boolean");
        }
    }

    public String toString(){
        switch (operation){
            case 1: return expression1.toString() + " && " + this.expression2.toString();
            case 2: return expression1.toString() + " || " + this.expression2.toString();
            default: return "";
        }
    }
}
