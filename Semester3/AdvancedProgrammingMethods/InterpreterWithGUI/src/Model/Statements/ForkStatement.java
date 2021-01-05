package Model.Statements;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyStack;
import Model.ADTs.MyStackInterface;
import Model.ProgramState;
import Model.Types.Type;

public class ForkStatement implements Statement{
    Statement statement;

    public ForkStatement(Statement statement) {
        this.statement = statement;
    }

    public ProgramState execute(ProgramState state) throws InterpreterException {
        MyStackInterface<Statement> newExecutionStack = new MyStack<>();
        newExecutionStack.push(statement);
        return new ProgramState(newExecutionStack,
                state.getSymbolTable().createCopy(), state.getOutputConsole(),
                state.getFileTable(), state.getHeap());
    }

    public MyDictionaryInterface<String, Type> typeCheck(MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException {
        statement.typeCheck(variableTypes.createCopy());
        return variableTypes;
    }

    @Override
    public String toString() {
        return "fork(" + statement.toString() + ")";
    }
}
