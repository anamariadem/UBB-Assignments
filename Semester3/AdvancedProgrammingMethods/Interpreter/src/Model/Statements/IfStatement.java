package Model.Statements;

import Exceptions.*;
import Model.ADTs.MyStackInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
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
    public ProgramState execute(ProgramState state) throws MyException, DivisionByZero, VariableDefinitionException, TypesDoNotMatch, InvalidDataType {
        MyStackInterface<Statement> stack = state.getExecutionStack();
        Value evaluation = this.expression.evaluate(state.getSymbolTable());
        if(evaluation.getType().equals(new BoolType())){
            if(evaluation.equals(new BoolValue(true)))
                stack.push(this.thenStatement);
            else
                stack.push(this.elseStatement);
        }else throw new InvalidDataType("Condition does not evaluate to boolean type");

        state.setExecutionStack(stack);
        return state;
    }

    public String toString() {
        return "( IF (" + this.expression.toString() + ") THEN (" + this.thenStatement.toString() + ") ELSE (" + this.elseStatement.toString() + "))";
    }
}
