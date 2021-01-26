package GUI;

import Controller.Controller;
import Exceptions.InterpreterException;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Statements.Statement;
import Model.Types.Type;
import Repository.Repository;
import Repository.RepositoryInterface;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Rectangle2D;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import OldView.CodeExamples;
import javafx.stage.Screen;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.ArrayList;

public class ListViewController {
    private ProgramExecutionController programExecutionController;

    @FXML
    private ListView<Statement> statementListView;

    @FXML
    private Button chooseProgramButton;

    public void setProgramExecutionController(ProgramExecutionController programExecutionController) {
        this.programExecutionController = programExecutionController;
    }

    @FXML
    public void initialize(){
        ArrayList<Statement> availablePrograms = CodeExamples.availablePrograms();
        statementListView.setItems(FXCollections.observableArrayList(availablePrograms));
        statementListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        chooseProgramButton.setOnAction(actionEvent -> {
            try {
                int selectedIndex = statementListView.getSelectionModel().getSelectedIndex();
                if (selectedIndex < 0)
                    return;
                ProgramState programState = new ProgramState(CodeExamples.availablePrograms().get(selectedIndex));
                RepositoryInterface repository = new Repository("logFile.txt");
                Controller controller = new Controller(repository);
                controller.addProgramState(programState);

//                try {
//                    MyDictionaryInterface<String, Type> variableTypes = new MyDictionary<>();
//                    programState.getExecutionStack().top().typeCheck(variableTypes);
//                }catch (InterpreterException exception){
//                    Alert alert = new Alert(Alert.AlertType.ERROR, exception.getMessage(), ButtonType.CLOSE);
//                    alert.showAndWait();
//                    return;
//                }

                FXMLLoader mainProgramLoader = new FXMLLoader();
                mainProgramLoader.setLocation(getClass().getResource("programExecution.fxml"));
                Parent programExecutionRoot = null;
                programExecutionRoot = mainProgramLoader.load();
                programExecutionController = mainProgramLoader.getController();
                programExecutionController.setController(controller);
                Stage stage = new Stage();
                stage.setTitle("Program execution");
                stage.setScene(new Scene(programExecutionRoot, 1200, 1180));
                stage.show();
            }
            catch (IOException exception) {
                exception.printStackTrace();
            }

            /*Alert alert = new Alert(Alert.AlertType.INFORMATION,
                    "Program " + CodeExamples.availablePrograms().get(selectedIndex).toString() + " was chosen!",
                    ButtonType.OK);
            alert.showAndWait();*/
        });

    }
}
