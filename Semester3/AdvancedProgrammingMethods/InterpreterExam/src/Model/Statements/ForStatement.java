package Model.Statements;


import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.BinaryExpression;
import Model.Expressions.Expression;
import Model.Expressions.RelationalExpression;
import Model.Expressions.VariableExpression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;

public class ForStatement implements Statement {
    String variableName;
    Expression startingValue;
    Expression endingValue;
    Expression stepSize;
    Statement statementToExecute;

    public ForStatement(String variableName, Expression startingValue, Expression endingValue, Expression stepSize, Statement statement) {
        this.variableName = variableName;
        this.startingValue = startingValue;
        this.endingValue = endingValue;
        this.stepSize = stepSize;
        this.statementToExecute = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        Statement statement = new CompoundStatement(
                new VariableDeclarationStatement(variableName, new IntType()),
                new CompoundStatement(
                        new AssignmentStatement(variableName, startingValue),
                        new WhileStatement(new RelationalExpression(
                                new VariableExpression(variableName),
                                endingValue,
                                BinaryExpression.OPERATION.LESS
                        ),
                                new CompoundStatement(
                                        statementToExecute,
                                        new AssignmentStatement(variableName, stepSize)
                                ))
                )
        );
        state.getExecutionStack().push(statement);
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        Type variableType = variableTypes.getElementWithKey(variableName);
        Type startValueType = startingValue.typeCheck(variableTypes);
        Type endValueType = endingValue.typeCheck(variableTypes);
        Type stepSizeType = stepSize.typeCheck(variableTypes);
        if(! variableType.equals(new IntType()))
            throw new InterpreterException("Typechecker: variable " + variableName + " is not of type int");

        if(! startValueType.equals(new IntType()))
            throw new InterpreterException("Typechecker: expression " + startingValue.toString() + " is not of type int");

        if(! endValueType.equals(new IntType()))
            throw new InterpreterException("Typechecker: expression " + endingValue.toString() + " is not of type int");

        if(! stepSizeType.equals(new IntType()))
            throw new InterpreterException("Typechecker: expression " + stepSize.toString() + " is not of type int");
        statementToExecute.typeCheck(variableTypes);
        return null;
    }

    @Override
    public String toString() {
        return "(For (" + variableName + " = " +startingValue.toString() + ";" + variableName+ " < "
                +endingValue.toString() + ";" + variableName + " = " + stepSize.toString() + ")" +
                statementToExecute.toString() + ")";
    }
}
