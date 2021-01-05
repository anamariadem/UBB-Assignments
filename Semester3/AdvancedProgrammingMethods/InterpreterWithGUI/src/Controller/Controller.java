package Controller;

import Exceptions.InterpreterException;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;
import Repository.RepositoryInterface;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

public class Controller {
    RepositoryInterface repository;
    ExecutorService executorService;
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

    public List<ProgramState> getProgramStates(){
        return repository.getProgramStatesList();
    }

    //collection because .values() from dictionary returns collection
    Set<AtomicInteger> getAddresses(List<Collection<Value>> symbolTableValues, HashMap<AtomicInteger, Value> heap){
        Set<AtomicInteger> addresses = new HashSet<>();
        symbolTableValues.forEach(symbolTable -> symbolTable.stream()
                .filter(value -> value instanceof ReferenceValue)
                .forEach(value -> {
                    while (value instanceof ReferenceValue){
                        AtomicInteger address = ((ReferenceValue) value).getAddress();
                        addresses.add(address);
                        value = heap.get(address);
                    }
                }));
        return addresses;
    }

    Map<AtomicInteger, Value> garbageCollector(Set<AtomicInteger> addresses, HashMap<AtomicInteger, Value> heap){
        return heap.entrySet()
                .stream()
                .filter(heapEntry -> addresses.contains(heapEntry.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<ProgramState> removeCompletedPrograms(List<ProgramState> programStates){
        return programStates.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public void conservativeGarbageCollector(List<ProgramState> programStateList){
        ProgramState programState = programStateList.get(0);

        List<Collection<Value>> symbolTableValues = programStateList.stream()
                .map(currentProgramState -> currentProgramState.getSymbolTable().getDictionary().values())
                .collect(Collectors.toList());

        HashMap<AtomicInteger, Value> heap = programState.getHeap().getDictionary();
        Set<AtomicInteger> addresses = getAddresses(symbolTableValues, heap);
        Map<AtomicInteger, Value> newHeap = garbageCollector(addresses, heap);
        programState.getHeap().setContent(newHeap);
    }

    //OLD METHOD!!!!
    /*public ProgramState oneStep(ProgramState state) throws InterpreterException {
        MyStackInterface<Statement> stack = state.getExecutionStack();
        if(stack.isEmpty()){
            throw new InterpreterException("Stack is empty");
        }
        Statement currentState = stack.pop();
        return currentState.execute(state);
    }*/

    public void oneStepForAllPrograms(List<ProgramState> programStates) throws InterpreterException {
        /*
        executes one step for each existing ProgramState (namely each thread)
         */

        //prepare the list of callables
        List<Callable<ProgramState>> callableList = programStates.stream()
                .map((ProgramState programState) -> (Callable<ProgramState>)(programState::oneStep))
                .collect(Collectors.toList());

        try {
            List<ProgramState> newProgramStatesList = executorService.invokeAll(callableList).stream()
                    .map(programStateFuture -> {
                        try {
                            return programStateFuture.get();
                        }catch (InterruptedException | InterpreterException | ExecutionException exception){
                            throw new InterpreterException(exception.getMessage());
                        }
                        //return null;
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());

            programStates.addAll(newProgramStatesList);

        }catch (InterruptedException interruptedException){
            throw new InterpreterException("An InterruptedException occured: " + interruptedException.getMessage());
        }

        programStates.forEach(programState -> {
            try {
                repository.logProgramStateExecution(programState);
            }catch (InterpreterException interpreterException){
                interpreterException.printStackTrace();
            }
        });

        repository.setProgramStatesList(programStates);
    }

    public void oneStep() throws InterpreterException{
        List<ProgramState> programStateList = removeCompletedPrograms(repository.getProgramStatesList());

        executorService = Executors.newFixedThreadPool(2);

        conservativeGarbageCollector(programStateList);
        oneStepForAllPrograms(programStateList);
        List<ProgramState> newList = removeCompletedPrograms(programStateList);
        if(newList.isEmpty())
            repository.setProgramStatesList(programStateList);
        else
            repository.setProgramStatesList(newList);
        executorService.shutdown();
    }

    public void setExecutorService(ExecutorService service){
        executorService = service;
    }

    public void shutDownExecutor(){
        executorService.shutdown();
    }

    public void setProgramStatesList(List<ProgramState> programStateList){
        repository.setProgramStatesList(programStateList);
    }

    public void allSteps(){
        MyDictionaryInterface<String, Type> variableTypes = new MyDictionary<>();
        ProgramState programState = repository.getProgramStatesList().get(0);
        programState.getExecutionStack().top().typeCheck(variableTypes);

        executorService = Executors.newFixedThreadPool(2);
        //before the execution, print the PrgState List into the log file

        repository.getProgramStatesList().forEach(currentProgramState -> {
            try {
                repository.logProgramStateExecution(currentProgramState);
            }catch (InterpreterException interpreterException){
                interpreterException.printStackTrace();
            }
        });
        //remove the completed programs
        List<ProgramState> programStateList = removeCompletedPrograms(repository.getProgramStatesList());

        //var programState = programStateList.get(0);

        while (programStateList.size() > 0){
            //cal garbage collector
            conservativeGarbageCollector(programStateList);
            oneStepForAllPrograms(programStateList);
            programStateList = removeCompletedPrograms(programStateList);
        }
        executorService.shutdown();

        repository.setProgramStatesList(programStateList);

        System.out.println(programState.getOutputConsole().toString());
    }

    //OLD METHOD
    /*public void allSteps() throws InterpreterException {
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
    }*/
}
