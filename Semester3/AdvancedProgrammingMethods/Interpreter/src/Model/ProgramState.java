package Model;

import Model.ADTs.*;
import Model.Statements.Statement;
import Model.Values.Value;

import java.io.BufferedReader;

public class ProgramState {
    private MyStackInterface<Statement> executionStack;
    private MyDictionaryInterface<String, Value> symbolTable;
    private MyListInterface<Value> outputConsole;
    private MyDictionaryInterface<String, BufferedReader> fileTable;
    private MyHeapInterface<Value> heap;
    private final Statement originalProgram;

    public ProgramState(Statement originalProgram){
        this.executionStack = new MyStack<>();
        this.symbolTable = new MyDictionary<>();
        this.outputConsole = new MyList<>();
        this.fileTable = new MyDictionary<>();
        this.heap = new MyHeap<>();
        this.originalProgram = originalProgram;
        if(originalProgram != null)
            executionStack.push(originalProgram);
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

    public MyDictionaryInterface<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public void setFileTable(MyDictionaryInterface<String, BufferedReader> fileTable) {
        this.fileTable = fileTable;
    }

    public MyHeapInterface<Value> getHeap() {
        return heap;
    }

    public void setHeap(MyHeapInterface<Value> heap) {
        this.heap = heap;
    }

    public String toString(){
        return " -------- Execution Stack -------- \n" +
                executionStack.toString() + "\n" +
                " -------- Symbol  Table -------- \n" +
                symbolTable.toString() + '\n' +
                " -------- Output Console-------- \n" +
                outputConsole.toString() + '\n' +
                " -------- File Table-------- \n" +
                fileTable.toString() + '\n' +
                " -------- Heap -------- \n" +
                heap.toString() + '\n' +
                " ------------------------------- \n\n";
    }

}
