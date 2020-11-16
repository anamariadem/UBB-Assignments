package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyStackInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Values.Value;

public class AssignmentStatement implements Statement{
    String variableName;
    Expression expression;

    public AssignmentStatement(String variableName, Expression expression){
        this.variableName = variableName;
        this.expression = expression;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException{
        MyStackInterface<Statement> stack = state.getExecutionStack();
        MyDictionaryInterface<String, Value> symbolTable = state.getSymbolTable();

        if(symbolTable.containsKey(this.variableName)){
            Value value = this.expression.evaluate(symbolTable, state.getHeap());
            if(value.getType().equals(symbolTable.getElementWithKey(this.variableName).getType())){
                symbolTable.update(this.variableName, value);
            }else {
                throw new InterpreterException("Types do not match");
            }
        }else {
            throw new InterpreterException("Variable is not defined");
        }
        return state;
    }

    public String toString(){
        return variableName + " = " + expression.toString();
    }
}
