package Controller;

import Exceptions.*;
import Model.ADTs.MyList;
import Model.ADTs.MyStackInterface;
import Model.ProgramState;
import Model.Statements.Statement;
import Model.Values.ReferenceValue;
import Model.Values.Value;
import Repository.RepositoryInterface;

import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Controller {
    RepositoryInterface repository;
    boolean displayFlag;

    public Controller(RepositoryInterface repository){
        this.repository = repository;
        this.displayFlag = false;
    }

    public void setDisplayFlag(boolean displayFlag) {
        this.displayFlag = displayFlag;
    }

    public String stateToString(ProgramState state){
        return state.toString();
    }

    public void addProgramState(ProgramState programState){
        this.repository.addProgramState(programState);
    }

    //collection because .values() from dictionary returns collection
    Set<AtomicInteger> getAddresses(Collection<Value> symbolTableValues, HashMap<AtomicInteger, Value> heap){
        Set<AtomicInteger> addresses = new HashSet<>();
        symbolTableValues.stream()
                .filter(value -> value instanceof ReferenceValue)
                .forEach(value -> {
                    while (value instanceof ReferenceValue){
                        AtomicInteger address = ((ReferenceValue) value).getAddress();
                        addresses.add(address);
                        value = heap.get(address);
                    }
                });
        return addresses;
    }

    Map<AtomicInteger, Value> garbageCollector(Set<AtomicInteger> addresses, HashMap<AtomicInteger, Value> heap){
        return heap.entrySet()
                .stream()
                .filter(heapEntry -> addresses.contains(heapEntry.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public ProgramState oneStep(ProgramState state) throws InterpreterException {
        MyStackInterface<Statement> stack = state.getExecutionStack();
        if(stack.isEmpty()){
            throw new InterpreterException("Stack is empty");
        }
        Statement currentState = stack.pop();
        return currentState.execute(state);
    }

    public void allSteps() throws InterpreterException{
        ProgramState programState = repository.getCurrentProgramState();
        //System.out.println("Initial state of the program");
        //System.out.println(programState.toString());
        repository.logProgramStateExecution(programState);
        while (!programState.getExecutionStack().isEmpty()){
            oneStep(programState);
            if(displayFlag) {
                //System.out.println(programState.toString());
                repository.logProgramStateExecution(programState);
            }

            Collection<Value> symbolTableValues = programState.getSymbolTable().getDictionary().values();
            HashMap<AtomicInteger, Value> heap = programState.getHeap().getDictionary();
            Set<AtomicInteger> addresses = getAddresses(symbolTableValues, heap);

            programState.getHeap().setContent(garbageCollector(addresses, heap));

        }
        System.out.println(programState.getOutputConsole().toString());
    }
}
