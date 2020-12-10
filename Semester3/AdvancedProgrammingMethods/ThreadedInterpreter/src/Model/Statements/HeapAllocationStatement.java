package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;

public class HeapAllocationStatement implements Statement{
    String variableName;
    Expression expression;

    public HeapAllocationStatement(String variableName, Expression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException {
        var symbolTable = state.getSymbolTable();
        var heap = state.getHeap();

        if(! symbolTable.containsKey(variableName))
            throw new InterpreterException("Variable " + variableName + " is not defined!");

        Value variableValue = symbolTable.getElementWithKey(variableName);
        if(! (variableValue.getType() instanceof ReferenceType))
            throw new InterpreterException("Variable " + variableName + " is not of Refrence Type!");

        Value evaluatedExpression = expression.evaluate(symbolTable, heap);
        Type locationType = ((ReferenceValue) variableValue).getLocationType();
        if(! locationType.equals(evaluatedExpression.getType()))
            throw new InterpreterException("Variable " + variableName + " is not of type " + evaluatedExpression.getType().toString());

        var address = heap.allocate();
        //update heap
        heap.add(address, evaluatedExpression);
        //update symbol table
        symbolTable.update(variableName, new ReferenceValue(address, evaluatedExpression.getType()));
        return null;
    }

    @Override
    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        var variableType = variableTypes.getElementWithKey(variableName);
        var expressionType = expression.typeCheck(variableTypes);

        if(!variableType.equals(new ReferenceType(expressionType)))
            throw new InterpreterException("Typechecker - The variable: " + variableName + " and the expression " + expression.toString() + " are of different types");

        return variableTypes;
    }

    @Override
    public String toString() {
        return "new(" + variableName + ", " + expression.toString() + ")";
    }
}
