package View;

import Controller.Controller;
import Model.ProgramState;
import Repository.Repository;
import Repository.RepositoryInterface;
import Model.Statements.*;
import Model.Expressions.*;
import Model.ADTs.*;
import Model.Types.*;
import Model.Values.*;

public class View {
    Controller controller;
    public View(Controller controller){
        this.controller = controller;
    }

    public void printMenu(){
        System.out.println("Available programs: ");
        System.out.println("Program 1: ");
        System.out.println("\tint v;\n\tv = 2;\n\tprint(v)");
        System.out.println("Program 2: ");
        //int a;int b; a=2+3*5;b=a+1;Print(b)
        System.out.println("\tint a;\n\tint b;\n\ta = 2 + 3 * 5\n\tb = a + 1;\n\tPrint(b)");
        System.out.println("Program 3: ");
        //bool a; int v; a=true;(If a Then v=2 Else v=3);Print(v)
        System.out.println("\tbool a;\n\tint v;\n\ta = true;\n\t(If a Then v=2 Else v=3);\n\tPrint(v)");
    }

    public void newProgram(int program) {
        ProgramState state;
        MyStackInterface<Statement> stack = new MyStack<Statement>();
        Statement ex1 = new CompoundStatement(
                new VariableDeclarationStatement(
                        "v",
                        new IntType()
                ),
                new CompoundStatement(
                        new AssignmentStatement(
                                "v",
                                new ValueExpression(
                                        new IntValue(2)
                                )
                        ),
                        new PrintStatement(
                                new VariableExpression(
                                        "v"
                                )
                        )
                )
        );
        Statement ex2 = new CompoundStatement(
                new VariableDeclarationStatement(
                        "a",
                        new IntType()),
                new CompoundStatement(new VariableDeclarationStatement(
                        "b",
                        new IntType()
                ),
                        new CompoundStatement(
                                new AssignmentStatement(
                                        "a",
                                        new ArithmeticExpression(
                                                new ValueExpression(
                                                        new IntValue(2)
                                                ),
                                                new ArithmeticExpression(
                                                        new ValueExpression(
                                                                new IntValue(3)
                                                        ),
                                                        new ValueExpression(
                                                                new IntValue(5)
                                                        ),
                                                        '*'
                                                ),
                                                '+'
                                        )
                                ),
                                new CompoundStatement(
                                        new AssignmentStatement(
                                                "b",
                                                new ArithmeticExpression(

                                                        new VariableExpression("a"),
                                                        new ValueExpression(
                                                                new IntValue(1)
                                                        ),
                                                        '+'
                                                )
                                        ),
                                        new PrintStatement(
                                                new VariableExpression("b")
                                        )
                                )
                        )
                )
        );
        Statement ex3 = new CompoundStatement(
                new VariableDeclarationStatement(
                        "a",
                        new BoolType()
                ),
                new CompoundStatement(new VariableDeclarationStatement(
                        "v",
                        new IntType()
                ),
                        new CompoundStatement(
                                new AssignmentStatement(
                                        "a",
                                        new ValueExpression(
                                                new BoolValue(true)
                                        )
                                ),
                                new CompoundStatement(
                                        new IfStatement(
                                                new VariableExpression("a"),
                                                new AssignmentStatement(
                                                        "v",
                                                        new ValueExpression(
                                                                new IntValue(2)
                                                        )
                                                ),
                                                new AssignmentStatement(
                                                        "v",
                                                        new ValueExpression(
                                                                new IntValue(3)
                                                        )
                                                )
                                        ),
                                        new PrintStatement(
                                                new VariableExpression("v")
                                        )
                                )
                        )
                )
        );
       if(program == 1)
           stack.push(ex1);
       else if (program == 2)
           stack.push(ex2);
       else
           stack.push(ex3);

        state = new ProgramState(stack, new MyDictionary<String, Value>(), new MyList<Value>(), null);
        controller.addProgramState(state);

    }
}
