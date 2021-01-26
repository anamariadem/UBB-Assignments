package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.BinaryExpression;
import Model.Expressions.Expression;
import Model.Expressions.RelationalExpression;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Value;

public class SwitchStatement implements Statement{
    Expression switchExpression;
    Expression firstCaseExpression;
    Expression secondCaseExpression;
    Statement firstCaseStatement;
    Statement secondCaseStatement;
    Statement defaultCaseStatement;

    public SwitchStatement(Expression switchExpression, Expression firstCaseExpression, Expression secondCaseExpression, Statement firstCaseStatement, Statement secondCaseStatement, Statement defaultCaseStatement) {
        this.switchExpression = switchExpression;
        this.firstCaseExpression = firstCaseExpression;
        this.secondCaseExpression = secondCaseExpression;
        this.firstCaseStatement = firstCaseStatement;
        this.secondCaseStatement = secondCaseStatement;
        this.defaultCaseStatement = defaultCaseStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        Statement statement =
                new IfStatement(new RelationalExpression(switchExpression, firstCaseExpression, BinaryExpression.OPERATION.EQUAL),
                                firstCaseStatement, new IfStatement(new RelationalExpression(switchExpression, secondCaseExpression, BinaryExpression.OPERATION.EQUAL),
                                secondCaseStatement, defaultCaseStatement));
        state.getExecutionStack().push(statement);
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        Type switchExpressionType = switchExpression.typeCheck(variableTypes);
        Type firstCaseExpressionType = firstCaseExpression.typeCheck(variableTypes);
        Type secondCaseExpressionType = secondCaseExpression.typeCheck(variableTypes);

        if(!(switchExpressionType.equals(firstCaseExpressionType) && firstCaseExpressionType.equals(secondCaseExpressionType)))
            throw new InterpreterException("Typechecker: the expressions " +
                    switchExpression.toString() +  " " +
                    firstCaseExpression.toString() + " " + secondCaseExpression.toString() + " are of different types");
        firstCaseStatement.typeCheck(variableTypes);
        secondCaseStatement.typeCheck(variableTypes);
        defaultCaseStatement.typeCheck(variableTypes);

        return null;
    }

    @Override
    public String toString() {
        return "(Switch (" + switchExpression.toString() + ")" +
                "(case (" + firstCaseExpression.toString() + ") : " + firstCaseStatement.toString() + ")" +
                "(case (" + secondCaseExpression.toString() + ") : " + secondCaseStatement.toString() + ")" +
                "( default: " + defaultCaseStatement.toString() + ")";
    }
}
