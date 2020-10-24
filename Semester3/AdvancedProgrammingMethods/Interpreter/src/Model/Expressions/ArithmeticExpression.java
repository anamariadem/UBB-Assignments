package Model.Expressions;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyDictionaryInterface;
import Model.Types.IntType;
import Model.Values.IntValue;
import Model.Values.Value;

public class ArithmeticExpression implements Expression{
    Expression expression1;
    Expression expression2;
    char operation;

    public ArithmeticExpression(Expression expression1, Expression expression2, char operation){
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operation = operation;
    }

    public Value evaluate(MyDictionaryInterface<String, Value> table) throws MyException, DivisionByZero {
        Value firstValueAfterEvaluation;
        Value secondValueAfterEvaluation;

        firstValueAfterEvaluation = this.expression1.evaluate(table);
        if(firstValueAfterEvaluation.getType().equals(new IntType())){
            secondValueAfterEvaluation = this.expression2.evaluate(table);
            if(secondValueAfterEvaluation.getType().equals(new IntType())){
                IntValue firstValueAsInt = (IntValue)firstValueAfterEvaluation;
                IntValue secondValueAsInt = (IntValue)secondValueAfterEvaluation;
                int firstTerm = firstValueAsInt.getValue();
                int secondTerm = secondValueAsInt.getValue();
                if(this.operation == '+')
                    return new IntValue(firstTerm + secondTerm);
                else if(this.operation == '-')
                    return new IntValue(firstTerm - secondTerm);
                else if(this.operation == '*')
                    return new IntValue(firstTerm * secondTerm);
                else if(this.operation == '/') {
                    if (secondTerm == 0)
                        throw new DivisionByZero("Division by 0");
                    return new IntValue(firstTerm / secondTerm);
                }
                else
                    throw new MyException("Invalid operation");
            }
            else {
                throw new MyException("Second operand is not an integer");
            }
        }
        else {
            throw new MyException("First operand is not an integer");
        }
    }

    public String toString(){
        switch (this.operation){
            case '+': return expression1.toString() + " + " + expression2.toString();
            case '-': return expression1.toString() + " - " + expression2.toString();
            case '*': return expression1.toString() + " * " + expression2.toString();
            case '/': return expression1.toString() + " / " + expression2.toString();
            default: return "";
        }
    }
}
