import Controller.Controller;
import Repository.*;
import View.View;

import java.util.Scanner;

public class Run {

    public static void main(String[] args) {
        RepositoryInterface repository = new Repository();
        Controller controller = new Controller(repository);
        View view = new View(controller);

        Scanner scanner = new Scanner(System.in);
        view.printMenu();
        System.out.println(">");
        int program = scanner.nextInt();
        view.newProgram(program);
        try {
            controller.allSteps();
        }catch (Exception exception){
            System.out.println(exception.getMessage());
        }
    }
}
