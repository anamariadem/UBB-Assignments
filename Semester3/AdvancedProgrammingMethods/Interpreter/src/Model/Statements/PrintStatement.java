package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyListInterface;
import Model.ADTs.MyStackInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Values.Value;

public class PrintStatement implements Statement{
    Expression expression;

    public PrintStatement(Expression expression){
        this.expression = expression;
    }

    public ProgramState execute(ProgramState state) throws MyException, DivisionByZero {
        //MyStackInterface<Statement> stack = state.getExecutionStack();
        MyListInterface<Value> outputConsole = state.getOutputConsole();
        outputConsole.add(this.expression.evaluate(state.getSymbolTable()));
        state.setOutputConsole(outputConsole);
        return state;
    }

    public String toString(){
        return "print(" + expression.toString() + ")";
    }
}
