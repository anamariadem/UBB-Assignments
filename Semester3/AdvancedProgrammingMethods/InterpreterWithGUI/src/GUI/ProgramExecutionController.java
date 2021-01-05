package GUI;

import Controller.Controller;
import Exceptions.InterpreterException;
import Model.ProgramState;
import Model.Statements.Statement;
import Model.Values.Value;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.util.*;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
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
    private List<ProgramState> programStates;

    public void setController(Controller controller) {
        this.controller = controller;
        this.programStates = controller.getProgramStates();
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
    private Button executeOneStepButton;

    @FXML
    private TextField numberOfProgramStatesTextField;

    @FXML
    public void initialize(){
        heapTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        symbolTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        variableAddressColumn.setCellValueFactory(feature ->
                new SimpleIntegerProperty(feature.getValue().getKey()).asObject());
        valueTableColumn.setCellValueFactory(feature ->
                new SimpleStringProperty(feature.getValue().getValue()));

        variableNameColumn.setCellValueFactory(feature ->
                new SimpleStringProperty(feature.getValue().getKey()));
        variableValueColumn.setCellValueFactory(features ->
                new SimpleStringProperty(features.getValue().getValue()));

        programStatesListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        programStatesListView.getSelectionModel().select("1");

        executeOneStepButton.setOnAction(actionEvent -> oneStep());
        programStatesListView.setOnMouseClicked(mouseEvent -> {
            populateListsAndTables();
        });
    }

    public ProgramState getRunningProgramState(){
        if(controller.getProgramStates().isEmpty())
            return null;

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
            numberOfProgramStatesTextField.clear();
            numberOfProgramStatesTextField.setText("There are " + controller.getProgramStates().size() + " programs running");

        }catch (InterpreterException exception){
            raiseAlert(exception.getMessage());
            closeWindow();
        }
    }

    private void raiseAlert(String message){
        Alert alert = new Alert(Alert.AlertType.ERROR, message, ButtonType.CLOSE);
        alert.showAndWait();
    }

    @FXML
    public void populateListsAndTables(){
        populateExecutionStack();
        populateOutputConsole();
        populateFileTable();
        populateProgramStatesList();
        populateSymbolTable();
        populateHeapTable();
    }

    @FXML
    private void populateExecutionStack(){
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

}
