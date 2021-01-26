package GUI;

import Controller.Controller;
import Exceptions.InterpreterException;
import Model.ProgramState;
import Model.Quadruple;
import Model.Statements.Statement;
import Model.Triplet;
import Model.Values.Value;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.util.*;
import java.util.concurrent.Executor;
import java.util.stream.Collectors;

/*
4 linii, 3 coloane
   0    1     2
0    text field
1  lh   lsy    lft
2  h   | sy  | ft
3  lo    ls    lpsl
4 o   | s   | psl
5    buton
 */

public class ProgramExecutionController {
    private Controller controller;

    public void setController(Controller controller) {
        this.controller = controller;
        populateExecutionStack();
        populateProgramStatesList();
        populateTextField();
    }

    @FXML
    private ListView<String> executionStackListView;

    @FXML
    private ListView<String> outputConsoleListView;

    @FXML
    private ListView<String> fileTableListView;

    @FXML
    private ListView<String> programStatesListView;

    @FXML
    private TableView<Map.Entry<String, String>> symbolTableView;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> variableNameColumn;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> variableValueColumn;

    @FXML
    private TableView<Map.Entry<Integer, String>> heapTableView;

    @FXML
    private TableColumn<Map.Entry<Integer, String>, Integer> variableAddressColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, String>, String> valueTableColumn;

    @FXML
    private TableView<Map.Entry<Integer, Integer>> lockTableView;

    @FXML
    private TableColumn<Map.Entry<Integer, Integer>, Integer> lockAddressColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, Integer>, Integer> programStateIdColumn;

    @FXML
    private TableView<Map.Entry<Integer, Integer>> latchTableView;

    @FXML
    private TableColumn<Map.Entry<Integer, Integer>, Integer> latchAddressColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, Integer>, Integer> expressionValueColumn;

    @FXML
    private TableView<Triplet<Integer, Integer, String>> countSemaphoreTableView;

    @FXML
    private TableColumn<Triplet<Integer, Integer, String>, Integer> countSemAddressColumn;

    @FXML
    private TableColumn<Triplet<Integer, Integer, String>, Integer> countSemExpressionValueColumn;

    @FXML
    private TableColumn<Triplet<Integer, Integer, String>, String> countSemListValuesColumn;

    @FXML
    private TableView<Quadruple<Integer, Integer, String, Integer>> toySemaphoreTableView;

    @FXML
    private TableColumn<Quadruple<Integer, Integer, String, Integer>, Integer> toySemAddressColumn;

    @FXML
    private TableColumn<Quadruple<Integer, Integer, String, Integer>, Integer> toySemValue1Column;

    @FXML
    private TableColumn<Quadruple<Integer, Integer, String, Integer>, String> toySemListValuesColumn;

    @FXML
    private TableColumn<Quadruple<Integer, Integer, String, Integer>, Integer> toySemValue2Column;

    @FXML
    private TableView<Triplet<Integer, Integer, String>> barrierTableView;

    @FXML
    private TableColumn<Triplet<Integer, Integer, String>, Integer> barrierAddressColumn;

    @FXML
    private TableColumn<Triplet<Integer, Integer, String>, Integer> barrierExpressionValueColumn;

    @FXML
    private TableColumn<Triplet<Integer, Integer, String>, String> barrierListValuesColumn;


    @FXML
    private Button executeOneStepButton;

    @FXML
    private TextField numberOfProgramStatesTextField;

    @FXML
    public void initialize(){
        heapTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        symbolTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        lockTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        latchTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        variableAddressColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getKey()).asObject());
        valueTableColumn.setCellValueFactory(feature ->
                new SimpleStringProperty(feature.getValue().getValue()));

        variableNameColumn.setCellValueFactory(feature ->
                new SimpleStringProperty(feature.getValue().getKey()));
        variableValueColumn.setCellValueFactory(features ->
                new SimpleStringProperty(features.getValue().getValue()));

        lockAddressColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getKey()).asObject());
        programStateIdColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getValue()).asObject());

        latchAddressColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getKey()).asObject());
        expressionValueColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getValue()).asObject());

        countSemAddressColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getFirst()).asObject());
        countSemExpressionValueColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getSecond()).asObject());
        countSemListValuesColumn.setCellValueFactory(features ->
                new SimpleStringProperty(features.getValue().getThird()));

        toySemAddressColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getFirst()).asObject());
        toySemValue1Column.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getSecond()).asObject());
        toySemValue2Column.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getFourth()).asObject());
        toySemListValuesColumn.setCellValueFactory(features ->
                new SimpleStringProperty(features.getValue().getThird()));

        barrierAddressColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getFirst()).asObject());
        barrierExpressionValueColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getSecond()).asObject());
        barrierListValuesColumn.setCellValueFactory(features ->
                new SimpleStringProperty(features.getValue().getThird()));

        programStatesListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        programStatesListView.getSelectionModel().select("1");

        executeOneStepButton.setOnAction(actionEvent -> oneStep());
        programStatesListView.setOnMouseClicked(mouseEvent -> {
            populateListsAndTables();
        });
    }


    public ProgramState getRunningProgramState(){
        int selectedIndex = programStatesListView.getSelectionModel().getSelectedIndex();
        if(selectedIndex < 0)
            return controller.getProgramStates().get(0);

        return controller.getProgramStates().get(selectedIndex);
    }

    private void closeWindow(){
        Stage stage = (Stage) executeOneStepButton.getScene().getWindow();
        stage.close();
    }


    public void oneStep(){
        try {
           if(controller.getProgramStates().get(0).getExecutionStack().isEmpty()) {
               programStatesListView.setItems(null);
               numberOfProgramStatesTextField.clear();
               numberOfProgramStatesTextField.setText("There are no programs running");
               raiseAlert("Nothing left to execute!");
               closeWindow();
               return;
            }
            controller.oneStep();
            populateListsAndTables();
            populateTextField();
            //numberOfProgramStatesTextField.clear();
            //numberOfProgramStatesTextField.setText("There are " + controller.getProgramStates().size() + " programs running");

        }catch (InterpreterException exception){
            raiseAlert(exception.getMessage());
            exception.printStackTrace();
            closeWindow();
        }
    }

    private void raiseAlert(String message){
        Alert alert = new Alert(Alert.AlertType.ERROR, message, ButtonType.CLOSE);
        alert.showAndWait();
    }

    private void populateTextField(){
        numberOfProgramStatesTextField.clear();
        numberOfProgramStatesTextField.setText("There are " + controller.getProgramStates().size() + " programs running");

    }

    @FXML
    public void populateListsAndTables(){
        populateExecutionStack();
        populateOutputConsole();
        populateFileTable();
        populateProgramStatesList();
        populateSymbolTable();
        populateHeapTable();
        populateLockTable();
        populateLatchTable();
        populateCountSemaphoreTable();
        populateToySemaphoreTable();
        populateBarrierTable();
    }

    @FXML
    public void populateExecutionStack(){
        ProgramState runningProgram = getRunningProgramState();
        List<String> stackToPopulate = runningProgram
                .getExecutionStack()
                .getStackContent()
                .stream()
                .map(Objects::toString)
                .collect(Collectors.toList());

        Collections.reverse(stackToPopulate);
        executionStackListView.setItems(FXCollections.observableArrayList(stackToPopulate));
        executionStackListView.refresh();
    }

    private void populateOutputConsole(){
        ProgramState runningProgram = getRunningProgramState();
        List<String> outputConsoleToPopulate = runningProgram
                .getOutputConsole()
                .getElements()
                .stream()
                .map(Objects::toString)
                .collect(Collectors.toList());

        outputConsoleListView.setItems(FXCollections.observableArrayList(outputConsoleToPopulate));
        outputConsoleListView.refresh();
    }

    private void populateFileTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<String> fileTableToPopulate = runningProgram
                .getFileTable()
                .getDictionary()
                .keySet()
                .stream()
                .map(Objects::toString)
                .collect(Collectors.toList());

        fileTableListView.setItems(FXCollections.observableArrayList(fileTableToPopulate));
        fileTableListView.refresh();
    }

    @FXML
    private void populateProgramStatesList(){
        List<String> programStatesToPopulate = controller
                .getProgramStates()
                .stream()
                .map(programState -> programState.getProgramStateId().get())
                .map(Objects::toString)
                .collect(Collectors.toList());

        programStatesListView.setItems(FXCollections.observableArrayList(programStatesToPopulate));
        programStatesListView.refresh();
    }

    private void populateSymbolTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<Map.Entry<String, String>> symTableString = new ArrayList<>();
        runningProgram.getSymbolTable()
                .getDictionary()
                .forEach((variableName, variableValue)-> {
                    symTableString.add(Map.entry(variableName, variableValue.toString()));
                });

        symbolTableView.setItems(FXCollections.observableArrayList(symTableString));
        symbolTableView.refresh();
    }

    private void populateHeapTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<Map.Entry<Integer, String>> heapString = new ArrayList<>();
        runningProgram.getHeap()
                .getDictionary()
                .forEach((address, value)-> {
                    heapString.add(Map.entry(address.get(), value.toString()));
                });

        heapTableView.setItems(FXCollections.observableArrayList(heapString));
        heapTableView.refresh();
    }

    private void populateLockTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<Map.Entry<Integer, Integer>> lockString = new ArrayList<>();
        runningProgram.getLockTable()
                .getDictionary()
                .forEach((address, value)-> {
                    lockString.add(Map.entry(address, value));
                });

        lockTableView.setItems(FXCollections.observableArrayList(lockString));
        lockTableView.refresh();
    }

    private void populateLatchTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<Map.Entry<Integer, Integer>> latchString = new ArrayList<>();
        runningProgram.getLatchTable()
                .getDictionary()
                .forEach((address, value)-> {
                    latchString.add(Map.entry(address, value));
                });

        latchTableView.setItems(FXCollections.observableArrayList(latchString));
        latchTableView.refresh();
    }

    private void populateCountSemaphoreTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<Triplet<Integer, Integer, String>> countSem = new ArrayList<>();
        runningProgram.getCountSemaphoreTable()
            .getDictionary()
            .forEach((address, value) ->
                    countSem.add(new Triplet<>(address, value.getKey(), value.getValue().toString())));

        countSemaphoreTableView.setItems(FXCollections.observableArrayList(countSem));
        countSemaphoreTableView.refresh();
    }

    private void populateToySemaphoreTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<Quadruple<Integer, Integer, String, Integer>> toySem = new ArrayList<>();
        runningProgram.getToySemaphoreTable()
                .getDictionary()
                .forEach((address, value) ->
                        toySem.add(new Quadruple<>(address, value.getFirst(),
                                value.getSecond().toString(),
                                value.getThird())));

        toySemaphoreTableView.setItems(FXCollections.observableArrayList(toySem));
        toySemaphoreTableView.refresh();
    }

    private void populateBarrierTable(){
        ProgramState runningProgram = getRunningProgramState();
        List<Triplet<Integer, Integer, String>> barrierValues = new ArrayList<>();
        runningProgram.getBarrierTable()
                .getDictionary()
                .forEach((address, value) ->
                        barrierValues.add(new Triplet<>(address, value.getKey(), value.getValue().toString())));

        barrierTableView.setItems(FXCollections.observableArrayList(barrierValues));
        barrierTableView.refresh();
    }

}