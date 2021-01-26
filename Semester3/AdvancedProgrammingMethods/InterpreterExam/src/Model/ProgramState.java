package Model;

import Exceptions.InterpreterException;
import Model.ADTs.*;
import Model.Statements.Statement;
import Model.Values.Value;
import javafx.util.Pair;

import java.io.BufferedReader;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class ProgramState {
    private final MyStackInterface<Statement> executionStack;
    private final MyDictionaryInterface<String, Value> symbolTable;
    private final MyListInterface<Value> outputConsole;
    private final MyDictionaryInterface<String, BufferedReader> fileTable;
    private MyHeapInterface<Value> heap;
    private final MyLockTableInterface<Integer> lockTable;
    private final MyLatchTableInterface<Integer> latchTable;
    private final MyToySemaphoreTableInterface<Triplet<Integer, List<Integer>, Integer>> toySemaphoreTable;
    private final MyCountSemaphoreTableInterface<Pair<Integer, List<Integer>>> countSemaphoreTable;
    private final MyBarrierTableInterface<Pair<Integer, List<Integer>>> barrierTable;
    //private final Statement originalProgram;
    private static final AtomicInteger lastProgramStateId = new AtomicInteger(1);
    private final AtomicInteger programStateId;


    public ProgramState(Statement originalProgram){
        this.executionStack = new MyStack<>();
        this.symbolTable = new MyDictionary<>();
        this.outputConsole = new MyList<>();
        this.fileTable = new MyDictionary<>();
        this.heap = new MyHeap<>();
        this.lockTable = new MyLockTable<>();
        this.latchTable = new MyLatchTable<>();
        this.toySemaphoreTable = new MyToySemaphoreTable<>();
        this.countSemaphoreTable = new MyCountSemaphoreTable<>();
        this.barrierTable = new MyBarrierTable<>();
        if(originalProgram != null)
            executionStack.push(originalProgram);
        programStateId = new AtomicInteger(1);
    }

    public ProgramState(MyStackInterface<Statement> executionStack, MyDictionaryInterface<String, Value> symbolTable,
                        MyListInterface<Value> outputConsole, MyDictionaryInterface<String, BufferedReader> fileTable,
                        MyHeapInterface<Value> heap, MyLockTableInterface<Integer> lockTable,
                        MyLatchTableInterface<Integer> latchTable,
                        MyToySemaphoreTableInterface<Triplet<Integer, List<Integer>, Integer>> toySemaphoreTable,
                        MyCountSemaphoreTableInterface<Pair<Integer, List<Integer>>> countSemaphoreTable,
                        MyBarrierTableInterface<Pair<Integer, List<Integer>>> barrierTable) {
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.outputConsole = outputConsole;
        this.fileTable = fileTable;
        this.heap = heap;
        this.lockTable = lockTable;
        this.latchTable = latchTable;
        this.toySemaphoreTable = toySemaphoreTable;
        this.countSemaphoreTable = countSemaphoreTable;
        this.barrierTable = barrierTable;
        programStateId = new AtomicInteger(newId());
    }

    public static synchronized int newId(){
        return lastProgramStateId.incrementAndGet();
    }

    /*public void setProgramStateId(){
        programStateId = new AtomicInteger(newId());
    }*/

    public MyStackInterface<Statement> getExecutionStack(){
        return this.executionStack;
    }

    public MyDictionaryInterface<String, Value> getSymbolTable(){
        return this.symbolTable;
    }

    public MyListInterface<Value> getOutputConsole(){
        return this.outputConsole;
    }

    public MyDictionaryInterface<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public MyHeapInterface<Value> getHeap() {
        return heap;
    }

    public AtomicInteger getProgramStateId() {
        return programStateId;
    }

    public void setHeap(MyHeapInterface<Value> heap) {
        this.heap = heap;
    }

    public MyLockTableInterface<Integer> getLockTable() {
        return lockTable;
    }

    public MyLatchTableInterface<Integer> getLatchTable() {
        return latchTable;
    }

    public MyToySemaphoreTableInterface<Triplet<Integer, List<Integer>, Integer>> getToySemaphoreTable() {
        return toySemaphoreTable;
    }

    public MyCountSemaphoreTableInterface<Pair<Integer, List<Integer>>> getCountSemaphoreTable() {
        return countSemaphoreTable;
    }

    public MyBarrierTableInterface<Pair<Integer, List<Integer>>> getBarrierTable() {
        return barrierTable;
    }

    public static AtomicInteger getLastProgramStateId() {
        return lastProgramStateId;
    }

    public boolean isNotCompleted(){
        return !executionStack.isEmpty();
    }

    public ProgramState oneStep() throws InterpreterException{
        if(executionStack.isEmpty())
            throw new InterpreterException("Execution stack is empty!");
        var currentStatement = executionStack.pop();
        return currentStatement.execute(this);
    }

    public String toString(){
        return  "Program id: " + programStateId + "\n" +
                " -------- Execution Stack -------- \n" +
                executionStack.toString() + "\n" +
                " -------- Symbol  Table -------- \n" +
                symbolTable.toString() + '\n' +
                " -------- Output Console-------- \n" +
                outputConsole.toString() + '\n' +
                " -------- File Table-------- \n" +
                fileTable.toString() + '\n' +
                " -------- Heap -------- \n" +
                heap.toString() + '\n' +
                " -------- Lock Table -------- \n" +
                lockTable.toString() + '\n' +
                " -------- Latch Table -------- \n" +
                latchTable.toString() + '\n' +
                " -------- Toy Semaphore Table -------- \n" +
                toySemaphoreTable.toString() + '\n' +
                " -------- Count Semaphore Table -------- \n" +
                countSemaphoreTable.toString() + '\n' +
                " -------- Barrier Table -------- \n" +
                barrierTable.toString() + '\n' +
                " ------------------------------- \n\n";
    }

}
