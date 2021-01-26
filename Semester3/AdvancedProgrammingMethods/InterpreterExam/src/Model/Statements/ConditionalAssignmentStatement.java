package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.Type;

public class ConditionalAssignmentStatement implements Statement{
    String variableName;
    Expression condition;
    Expression thenExpression;
    Expression elseExpression;


    public ConditionalAssignmentStatement(String variableName, Expression condition, Expression thenExpression, Expression elseExpression) {
        this.variableName = variableName;
        this.condition = condition;
        this.thenExpression = thenExpression;
        this.elseExpression = elseExpression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        if(! state.getSymbolTable().containsKey(variableName))
            throw new InterpreterException("Variable " + variableName + " is not defined");
        Statement statement = new IfStatement(condition,
                new AssignmentStatement(variableName, thenExpression),
                new AssignmentStatement(variableName, elseExpression));
        state.getExecutionStack().push(statement);
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        Type conditionType = condition.typeCheck(variableTypes);
        if(! conditionType.equals(new BoolType()))
            throw new InterpreterException("Typechekcer: Condition " + condition.toString() + " was not evaluated to bool"
            + conditionType.toString());

        Type thenExpressionType = thenExpression.typeCheck(variableTypes);
        Type elseExpressionType = elseExpression.typeCheck(variableTypes);
        Type variableType = variableTypes.getElementWithKey(variableName);

        if(! (variableType.equals(elseExpressionType) && elseExpressionType.equals(thenExpressionType)))
            throw new InterpreterException("Typechecker: the expressions " +
                variableName +  " " +
                thenExpression.toString() + " " + elseExpression.toString() + " are of different types");

        return variableTypes;
    }

    @Override
    public String toString() {
        return variableName + " = " + condition.toString() + " ? " + thenExpression.toString() + " : " + elseExpression.toString();
    }
}
