package Model.Statements;

import Exceptions.*;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyStackInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;

public class IfStatement implements Statement {
    Expression expression;
    Statement thenStatement;
    Statement elseStatement;

    public IfStatement(Expression expression, Statement thenStatement, Statement elseStatement){
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }
    public ProgramState execute(ProgramState state) throws InterpreterException{
        MyStackInterface<Statement> stack = state.getExecutionStack();
        Value evaluation = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        if(evaluation.getType().equals(new BoolType())){
            if(evaluation.equals(new BoolValue(true)))
                stack.push(this.thenStatement);
            else
                stack.push(this.elseStatement);
        }else throw new InterpreterException("Condition does not evaluate to boolean type");

        return null;
    }

    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        var expressionType = expression.typeCheck(variableTypes);

        if(! expressionType.equals(new BoolType()))
            throw new InterpreterException("Typechecker - The IF condition: " + expression.toString() + " id not of type bool");

        thenStatement.typeCheck(variableTypes.createCopy());
        elseStatement.typeCheck(variableTypes.createCopy());
        return variableTypes;
    }

    public String toString() {
        return "( IF (" + this.expression.toString() + ") THEN (" + this.thenStatement.toString() + ") ELSE (" + this.elseStatement.toString() + "))";
    }
}
