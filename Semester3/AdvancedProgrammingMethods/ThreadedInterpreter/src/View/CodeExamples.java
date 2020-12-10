package View;

import Model.Expressions.*;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.ReferenceType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;

import java.util.ArrayList;

public class CodeExamples {

    public static Statement buildProgram(Statement... statements){
        if (statements.length == 0)
            return new NopStatement();
        if (statements.length == 1)
            return statements[0];

        Statement finalStatement = new CompoundStatement(statements[statements.length - 2], statements[statements.length -1]);
        for (int i = statements.length - 3; i >= 0; i--)
            finalStatement = new CompoundStatement(statements[i], finalStatement);

        return finalStatement;
    }

    public static ArrayList<Statement> availablePrograms(){
        ArrayList<Statement> programs = new ArrayList<>();

        Statement program1 = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                new PrintStatement(new VariableExpression("v"))
        );

        //int a;int b; a=2+3*5;b=a+1;Print(b)
        Statement program2 = buildProgram(
                new VariableDeclarationStatement("a", new IntType()),
                new VariableDeclarationStatement("b", new IntType()),
                new AssignmentStatement("a",
                        new ArithmeticExpression(new ValueExpression(new IntValue(2)),
                                new ArithmeticExpression(new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)) , BinaryExpression.OPERATION.MULTIPLICATION),
                                    BinaryExpression.OPERATION.ADDITION)),
                new AssignmentStatement("b",
                        new ArithmeticExpression(new VariableExpression("a"),
                                new ValueExpression(new IntValue(1)), BinaryExpression.OPERATION.ADDITION)),
                new PrintStatement(new VariableExpression("b"))
        );

        //bool a; int v; a=true;(If a Then v=2 Else v=3);Print(v)
        Statement program3 = buildProgram(
                new VariableDeclarationStatement("a", new BoolType()),
                new VariableDeclarationStatement("v", new IntType()),
                new AssignmentStatement("a", new ValueExpression(new BoolValue(true))),
                new IfStatement(new VariableExpression("a"),
                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new AssignmentStatement("v", new ValueExpression(new IntValue(3)))),
                new PrintStatement(new VariableExpression("v"))
        );

        //string file ; file = file.txt ; open(file) ; int x ; READ(x, file) ; print(x) ; READ(x, file) ; print(x) ; close(file)
        Statement program4 = buildProgram(
                new VariableDeclarationStatement("file", new StringType()),
                new AssignmentStatement("file",
                        new ValueExpression(new StringValue("file.txt"))),
                new OpenFileStatement(new VariableExpression("file")),
                new VariableDeclarationStatement("x", new IntType()),
                new ReadFromFileStatement(new VariableExpression("file"), "x"),
                new PrintStatement(new VariableExpression("x")),
                new ReadFromFileStatement(new VariableExpression("file"), "x"),
                new PrintStatement(new VariableExpression("x")),
                new CloseFileStatement(new VariableExpression("file"))
        );

        //int x ; x = true ; print(x)
        Statement program5 = buildProgram(
               new VariableDeclarationStatement("x", new IntType()),
               new AssignmentStatement("x", new ValueExpression(new BoolValue(true))),
               new PrintStatement(new VariableExpression("x"))
        );

        //int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        Statement program6 = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                new WhileStatement(
                        new RelationalExpression(new VariableExpression("v"),
                                new ValueExpression(new IntValue(0)),
                                    BinaryExpression.OPERATION.MORE),

                        buildProgram(new PrintStatement(new VariableExpression("v")),
                                new AssignmentStatement("v",
                                new ArithmeticExpression(new VariableExpression("v"),
                                        new ValueExpression(new IntValue(1)),
                                            BinaryExpression.OPERATION.SUBTRACTION)))
                )

        );

        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        Statement program7 = buildProgram(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                new HeapAllocationStatement("a", new VariableExpression("v")),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new VariableExpression("a"))
        );

        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
        Statement program8 = buildProgram(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                new HeapAllocationStatement("a", new VariableExpression("v")),
                new PrintStatement(
                        new ReadHeapExpression(new VariableExpression("v"))),
                new PrintStatement(
                        new ArithmeticExpression(
                                new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))),
                                new ValueExpression(new IntValue(5)),
                                BinaryExpression.OPERATION.ADDITION
                        ))
        );

        //Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);
        Statement program9 = buildProgram(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new PrintStatement(
                        new ReadHeapExpression(new VariableExpression("v"))),
                new WriteHeapStatement("v", new ValueExpression(new IntValue(30))),
                new PrintStatement(
                        new ArithmeticExpression(
                                new ReadHeapExpression(new VariableExpression("v")),
                                new ValueExpression(new IntValue(5)),
                                BinaryExpression.OPERATION.ADDITION
                        ))
        );

        //Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
        Statement program10 = buildProgram(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                new HeapAllocationStatement("a", new VariableExpression("v")),
                new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                new PrintStatement(new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))))
        );

        Statement program11 = buildProgram(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("v")))
        );

        //int v; Ref int a; v=10;new(a,22);fork(wH(a,30);v=32;print(v);print(rH(a)));print(v);print(rH(a))
        Statement program12 = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                new ForkStatement(
                        buildProgram(
                                new WriteHeapStatement("a", new ValueExpression(new IntValue(30))),
                                new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                        )
                ),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
        );

        //int v; Ref int a; v=10;new(a,22);fork(wH(a,30);v=32;new(a, 33);print(v);print(rH(a)));print(v);print(rH(a))
        Statement program13 = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                new ForkStatement(
                        buildProgram(
                                new WriteHeapStatement("a", new ValueExpression(new IntValue(30))),
                                new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                new HeapAllocationStatement("a", new ValueExpression(new IntValue(33))),
                                new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                        )
                ),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
        );

        //int v; Ref int a; v=10;new(a,22);fork(wH(a,30);v=32;print(v);print(rH(a)));print(v);print(rH(a))
        Statement program14 = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                new ForkStatement(
                        buildProgram(
                                new WriteHeapStatement("a", new ValueExpression(new IntValue(30))),
                                new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a"))),
                                new PrintStatement(new ArithmeticExpression(
                                        new ValueExpression(new BoolValue(true)),
                                        new ValueExpression(new IntValue(3)),
                                        BinaryExpression.OPERATION.ADDITION
                                ))
                        )
                ),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
        );

        programs.add(program1);
        programs.add(program2);
        programs.add(program3);
        programs.add(program4);
        programs.add(program5);
        programs.add(program6);
        programs.add(program7);
        programs.add(program8);
        programs.add(program9);
        programs.add(program10);
        programs.add(program11);
        programs.add(program12);
        programs.add(program13);
        programs.add(program14);
        return programs;
    }
}
