package View;

import Model.ADTs.MyDictionary;
import Model.ADTs.MyDictionaryInterface;

import java.util.Scanner;

public class TextMenu {
    private final MyDictionaryInterface<String, Command> commands;

    public TextMenu() {
        commands = new MyDictionary<String, Command>();
    }

    public void addCommand(Command command){
        commands.add(command.getKey(), command);
    }

    private void printMenu(){
        for(String com : commands.keySet()){
            String line=String.format("%4s : %s", commands.getElementWithKey(com).getKey(), commands.getElementWithKey(com).getDescription());
            System.out.println(line);
        }
    }
    public void show(){
        Scanner scanner=new Scanner(System.in);
        while(true){
            printMenu();
            System.out.print("Input the option: ");
            String key = scanner.nextLine();
            Command command = commands.getElementWithKey(key);
            if (command==null){
                System.out.println("Invalid Option");
                continue;
            }
            command.execute();
        }
    }
}
