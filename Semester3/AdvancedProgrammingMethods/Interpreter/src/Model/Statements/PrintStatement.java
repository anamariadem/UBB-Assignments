package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyListInterface;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Values.Value;

public class PrintStatement implements Statement{
    Expression expression;

    public PrintStatement(Expression expression){
        this.expression = expression;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException{
        MyListInterface<Value> outputConsole = state.getOutputConsole();
        outputConsole.add(this.expression.evaluate(state.getSymbolTable(), state.getHeap()));

        return state;
    }

    public String toString(){
        return "print(" + expression.toString() + ")";
    }
}
