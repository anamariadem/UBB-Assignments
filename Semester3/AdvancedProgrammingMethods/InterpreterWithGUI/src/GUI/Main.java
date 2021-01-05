package GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("listView.fxml"));
        Parent root = fxmlLoader.load();
        ListViewController listViewController = fxmlLoader.getController();
        primaryStage.setTitle("Select program to be executed");
        primaryStage.setScene(new Scene(root, 800, 450));
        primaryStage.show();

        /*FXMLLoader mainProgramLoader = new FXMLLoader();
        mainProgramLoader.setLocation(getClass().getResource("programExecution.fxml"));
        Parent programExecutionRoot = mainProgramLoader.load();

        ProgramExecutionController programExecutionController = mainProgramLoader.getController();
        listViewController.setProgramExecutionController(programExecutionController);

        Stage stage = new Stage();
        stage.setTitle("Program execution");
        stage.setScene(new Scene(programExecutionRoot, 1500, 845));
        stage.show();*/

    }


    public static void main(String[] args) {
        launch(args);
    }
}
