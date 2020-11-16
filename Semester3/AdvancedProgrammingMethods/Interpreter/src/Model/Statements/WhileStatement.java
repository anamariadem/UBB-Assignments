package Model.Statements;

import Exceptions.InterpreterException;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Value;

public class WhileStatement implements Statement{
    Expression whileCondition;
    Statement statementToBeExecuted;

    public WhileStatement(Expression whileCondition, Statement statementToBeExecuted) {
        this.whileCondition = whileCondition;
        this.statementToBeExecuted = statementToBeExecuted;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException {
        var executionStack = state.getExecutionStack();

        Value evaluatedExpression = whileCondition.evaluate(state.getSymbolTable(), state.getHeap());
        if(! evaluatedExpression.getType().equals(new BoolType()))
            throw new InterpreterException("Expression " + evaluatedExpression.toString() + " was not evaluated to Bool Type");

        BoolValue boolValue = (BoolValue) evaluatedExpression;
        if(boolValue.getValue()){
            executionStack.push(this);
            executionStack.push(statementToBeExecuted);
        }

        return state;
    }

    public String toString() {
        return "While(" + whileCondition.toString() + ") { \t" + statementToBeExecuted.toString() + "\t}";
    }
}
