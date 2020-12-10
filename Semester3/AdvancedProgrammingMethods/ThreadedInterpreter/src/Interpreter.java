import Controller.Controller;
import Exceptions.InterpreterException;
import Model.ProgramState;
import Model.Statements.Statement;
import Repository.Repository;
import Repository.RepositoryInterface;
import View.*;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Interpreter {

    public static void clearFile(String fileName) throws InterpreterException {
        try {
            var fr = new FileWriter(fileName, false);
            fr.close();
        }catch (IOException exception){
            throw new InterpreterException("An IO exception ocuured: " + exception.getMessage());
        }
    }

    public static void main(String[] args) {
        /*Scanner scanner = new Scanner(System.in);
        System.out.println("Give file name: ");
        String fileName = scanner.nextLine();*/

        String fileName = "logFile.txt";

        try {
            clearFile(fileName);
        }catch (InterpreterException exception){
            System.out.println(exception.getMessage());
            return;
        }

        TextMenu textMenu = new TextMenu();
        ArrayList<Statement> statements = CodeExamples.availablePrograms();

        for(int i= 0; i <statements.size(); i++){
            ProgramState programState = new ProgramState(statements.get(i));
            RepositoryInterface repository = new Repository(fileName);
            Controller controller = new Controller(repository);
            controller.addProgramState(programState);
            controller.setDisplayFlag(true);
            Command runExample = new RunExample(Integer.toString(i+1), statements.get(i).toString(), controller);
            textMenu.addCommand(runExample);
        }

        Command exitCommand = new ExitCommand("0", "Exit");
        textMenu.addCommand(exitCommand);

        textMenu.show();
    }
}
