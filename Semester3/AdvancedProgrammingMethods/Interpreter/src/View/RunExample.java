package View;

import Controller.Controller;
import Exceptions.InterpreterException;

public class RunExample extends Command{
    Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {
            controller.allSteps();
        }catch (InterpreterException e){
            System.out.println("An exception occured: " + e.getMessage());
        }
    }
}
