package Model;

import Model.ADTs.MyDictionaryInterface;
import Model.ADTs.MyListInterface;
import Model.ADTs.MyStackInterface;
import Model.Statements.Statement;
import Model.Values.Value;

public class ProgramState {
    private MyStackInterface<Statement> executionStack;
    private MyDictionaryInterface<String, Value> symbolTable;
    private MyListInterface<Value> outputConsole;
    private final Statement originalProgram;

    public ProgramState(MyStackInterface<Statement> executionStack, MyDictionaryInterface<String, Value> symbolTable, MyListInterface<Value> outputConsole, Statement originalProgram){
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.outputConsole = outputConsole;
        this.originalProgram = originalProgram;
    }

    public MyStackInterface<Statement> getExecutionStack(){
        return this.executionStack;
    }

    public void setExecutionStack(MyStackInterface<Statement> executionStack){
        this.executionStack = executionStack;
    }

    public MyDictionaryInterface<String, Value> getSymbolTable(){
        return this.symbolTable;
    }

    public void setSymbolTable(MyDictionaryInterface<String, Value> symbolTable){
        this.symbolTable = symbolTable;
    }

    public MyListInterface<Value> getOutputConsole(){
        return this.outputConsole;
    }

    public void setOutputConsole(MyListInterface<Value> outputConsole){
        this.outputConsole = outputConsole;
    }

    public Statement getOriginalProgram() {
        return originalProgram;
    }

    public String toString(){
        return " -------- Execution Stack -------- \n" +
                executionStack.toString() + "\n" +
                " -------- Symbol  Table -------- \n" +
                symbolTable.toString() + '\n' +
                " -------- Output Console-------- \n" +
                outputConsole.toString() + '\n' +
                " ------------------------------- \n\n";
    }

}
