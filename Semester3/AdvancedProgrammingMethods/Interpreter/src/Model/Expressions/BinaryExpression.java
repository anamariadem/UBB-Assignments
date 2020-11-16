package Model.Expressions;

public abstract class BinaryExpression implements Expression{
    protected Expression leftSideExpression;
    protected Expression rightSideExpression;
    protected OPERATION operation;

    public enum OPERATION{
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        AND,
        OR,
        LESS,
        LESS_OR_EQUAL,
        MORE,
        MORE_OR_EQUAL,
        EQUAL,
        NOT_EQUAL
    }

    public BinaryExpression(Expression leftSideExpression, Expression rightSideExpression, OPERATION operation) {
        this.leftSideExpression = leftSideExpression;
        this.rightSideExpression = rightSideExpression;
        this.operation = operation;
    }

    public String toString(){
        return leftSideExpression.toString() + " " +
                operation.toString() + " " +
                rightSideExpression.toString();
    }
}
