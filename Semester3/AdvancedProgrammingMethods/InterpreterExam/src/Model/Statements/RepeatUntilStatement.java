package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.Expressions.NotExpression;
import Model.Expressions.RelationalExpression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.Type;

public class RepeatUntilStatement implements Statement{
    Statement statementToExecute;
    Expression condition;

    public RepeatUntilStatement(Statement statementToExecute, Expression condition) {
        this.statementToExecute = statementToExecute;
        this.condition = condition;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        Statement statement = new CompoundStatement(
                statementToExecute,
                new WhileStatement(new NotExpression(condition), statementToExecute)
        );
        state.getExecutionStack().push(statement);
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        var expressionType = condition.typeCheck(variableTypes);

        if(! expressionType.equals(new BoolType()))
            throw new InterpreterException("Typechecker - The condition: " + condition.toString() + " is not of type bool");

        statementToExecute.typeCheck(variableTypes.createCopy());
        return variableTypes;
    }

    @Override
    public String toString() {
        return "(Repeat (" + statementToExecute.toString() + ") until " + condition.toString() + ")";
    }
}
