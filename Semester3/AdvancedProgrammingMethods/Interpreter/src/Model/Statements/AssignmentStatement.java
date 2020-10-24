package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Exceptions.TypesDoNotMatch;
import Exceptions.VariableDefinitionException;
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
    public ProgramState execute(ProgramState state) throws MyException, DivisionByZero, VariableDefinitionException, TypesDoNotMatch {
        MyStackInterface<Statement> stack = state.getExecutionStack();
        MyDictionaryInterface<String, Value> symbolTable = state.getSymbolTable();
        if(symbolTable.isVariableDefined(this.variableName)){
            Value value = this.expression.evaluate(symbolTable);
            if(value.getType().equals(symbolTable.getElementWithKey(this.variableName).getType())){
                symbolTable.update(this.variableName, value);
            }else {
                throw new TypesDoNotMatch("Types do not match");
            }
        }else {
            throw new VariableDefinitionException("Variable is not defined");
        }
        state.setSymbolTable(symbolTable);
        return state;
    }

    public String toString(){
        return variableName + " = " + expression.toString();
    }
}
