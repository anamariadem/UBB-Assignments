package OldView;

import Model.Expressions.*;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.ReferenceType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;

import javax.swing.plaf.nimbus.State;
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
                                new ArithmeticExpression(new ValueExpression(new IntValue(3)),
                                        new ValueExpression(new IntValue(5)) ,
                                        BinaryExpression.OPERATION.MULTIPLICATION),
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

        //switch
//        int a; int b; int c;
//        a=1;b=2;c=5;
//        (switch(a*10)
//        (case (b*c) : print(a);print(b))
//        (case (10) : print(100);print(200))
//        (default : print(300)));
//        print(300)

        Statement programSwitch = buildProgram(
                new VariableDeclarationStatement("a", new IntType()),
                new VariableDeclarationStatement("b", new IntType()),
                new VariableDeclarationStatement("c", new IntType()),
                new AssignmentStatement("a", new ValueExpression(new IntValue(1))),
                new AssignmentStatement("b", new ValueExpression(new IntValue(2))),
                new AssignmentStatement("c", new ValueExpression(new IntValue(5))),
                new SwitchStatement(new ArithmeticExpression(
                            new VariableExpression("a"),
                            new ValueExpression(new IntValue(10)),
                            BinaryExpression.OPERATION.MULTIPLICATION),

                        new ArithmeticExpression(
                               new VariableExpression("b"),
                               new VariableExpression("c"),
                               BinaryExpression.OPERATION.MULTIPLICATION),

                        new ValueExpression(new IntValue(10)),

                        buildProgram(
                                new PrintStatement(new VariableExpression("a")),
                                new PrintStatement(new VariableExpression("b"))
                        ),

                        buildProgram(
                                new PrintStatement(new ValueExpression(new IntValue(100))),
                                new PrintStatement(new ValueExpression(new IntValue(200)))
                        ),

                        new PrintStatement(new ValueExpression(new IntValue(300)))
                ),
                new PrintStatement(new ValueExpression(new IntValue(300)))
        );
        //cond assign
//        Ref int a; Ref int b; int v;
//        new(a,0); new(b,0);
//        wh(a,1); wh(b,2);
//        v=(rh(a)<rh(b))?100:200;
//        print(v);
//        v= ((rh(b)-2)>rh(a))?100:200;
//        print(v);

        Statement programCondAssign = buildProgram(
                new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("b", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("v", new IntType()),
                new HeapAllocationStatement("a", new ValueExpression(new IntValue(0))),
                new HeapAllocationStatement("b", new ValueExpression(new IntValue(0))),
                new WriteHeapStatement("a", new ValueExpression(new IntValue(1))),
                new WriteHeapStatement("b", new ValueExpression(new IntValue(2))),
                new ConditionalAssignmentStatement(
                        "v",
                        new RelationalExpression(new ReadHeapExpression(new VariableExpression("a")),
                                    new ReadHeapExpression(new VariableExpression("b")),
                                    BinaryExpression.OPERATION.LESS),
                                new ValueExpression(new IntValue(100)),
                                new ValueExpression(new IntValue(200))

                ),
                new PrintStatement(new VariableExpression("v")),
                new ConditionalAssignmentStatement("v",
                        new RelationalExpression(
                            new ArithmeticExpression(
                                new ReadHeapExpression(new VariableExpression("b")),
                                new ValueExpression(new IntValue(2)),
                                BinaryExpression.OPERATION.SUBTRACTION
                            ),
                            new ReadHeapExpression(new VariableExpression("a")),
                            BinaryExpression.OPERATION.MORE
                        ),
                        new ValueExpression(new IntValue(100)),
                        new ValueExpression(new IntValue(200))
                ),
                new PrintStatement(new VariableExpression("v"))
        );

        //for
//        Ref int a; new(a,20);
//        (for(v=0;v<3;v=v+1) fork(print(v);v=v*rh(a)));
//        print(rh(a))

        Statement programFor = buildProgram(
                new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                new HeapAllocationStatement("a", new ValueExpression(new IntValue(20))),
                new ForStatement(
                        "v",
                        new ValueExpression(new IntValue(0)),
                        new ValueExpression(new IntValue(3)),
                        new ArithmeticExpression(new VariableExpression("v"),
                                new ValueExpression(new IntValue(1)),
                                BinaryExpression.OPERATION.ADDITION),
                        new ForkStatement(
                                buildProgram(
                                        new PrintStatement(new VariableExpression("v")),
                                        new AssignmentStatement("v", new ArithmeticExpression(
                                                new VariableExpression("v"),
                                                new ReadHeapExpression(new VariableExpression("a")),
                                                BinaryExpression.OPERATION.MULTIPLICATION
                                        ))
                                )
                        )
                ),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
        );
        //repeat until
//        v=0;
//        (repeat (fork(print(v);v=v-1);v=v+1) until v==3);
//        x=1;y=2;z=3;w=4;
//        print(v*10)
        Statement programRepeatUntil = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new RepeatUntilStatement(
                        buildProgram(
                                new ForkStatement(
                                        new CompoundStatement(
                                                new PrintStatement(new VariableExpression("v")),
                                                new AssignmentStatement("v", new ArithmeticExpression(
                                                        new VariableExpression("v"),
                                                        new ValueExpression(new IntValue(1)),
                                                        BinaryExpression.OPERATION.SUBTRACTION
                                                ))
                                        )
                                ),
                                new AssignmentStatement("v", new ArithmeticExpression(
                                        new VariableExpression("v"),
                                        new ValueExpression(new IntValue(1)),
                                        BinaryExpression.OPERATION.ADDITION
                                ))
                ),
                        new RelationalExpression(new VariableExpression("v"),
                                new ValueExpression(new IntValue(3)),
                                BinaryExpression.OPERATION.EQUAL)
                ),
                new PrintStatement(new ArithmeticExpression(new VariableExpression("v"),
                        new ValueExpression(new IntValue(10)),
                        BinaryExpression.OPERATION.MULTIPLICATION))
        );

        //sleep
//        v=10;
//        (fork(v=v-1;v=v-1;print(v)); sleep(10);print(v*10)
        Statement programSleep = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                new ForkStatement(buildProgram(
                        new AssignmentStatement("v", new ArithmeticExpression(
                                new VariableExpression("v"),
                                new ValueExpression(new IntValue(1)),
                                BinaryExpression.OPERATION.SUBTRACTION
                        )),
                        new AssignmentStatement("v", new ArithmeticExpression(
                                new VariableExpression("v"),
                                new ValueExpression(new IntValue(1)),
                                BinaryExpression.OPERATION.SUBTRACTION
                        )),
                        new PrintStatement(new VariableExpression("v"))
                )),
                new SleepStatement(10),
                new PrintStatement(new ArithmeticExpression(
                        new VariableExpression("v"),
                        new ValueExpression(new IntValue(10)),
                        BinaryExpression.OPERATION.MULTIPLICATION
                ))
        );
        //sleep
//        v=0;
//        (while(v<3) (fork(print(v);v=v+1);v=v+1);
//        sleep(5);
//        print(v*10)
        Statement programSleep2 = buildProgram(
                new VariableDeclarationStatement("v", new IntType()),
                new WhileStatement(new RelationalExpression(
                        new VariableExpression("v"),
                        new ValueExpression(new IntValue(3)),
                        BinaryExpression.OPERATION.LESS
                ),buildProgram(new ForkStatement(
                        buildProgram(
                                new PrintStatement(new VariableExpression("v")),
                                new AssignmentStatement("v",new ArithmeticExpression(
                                        new VariableExpression("v"),
                                        new ValueExpression(new IntValue(1)),
                                        BinaryExpression.OPERATION.ADDITION
                                ))
                        )),
                        new AssignmentStatement("v",new ArithmeticExpression(
                                new VariableExpression("v"),
                                new ValueExpression(new IntValue(1)),
                                BinaryExpression.OPERATION.ADDITION
                        ))
                )),
                new SleepStatement(5),
                new PrintStatement(new ArithmeticExpression(
                        new VariableExpression("v"),
                        new ValueExpression(new IntValue(10)),
                        BinaryExpression.OPERATION.MULTIPLICATION
                ))
        );

        Statement programLock = buildProgram(
                new VariableDeclarationStatement("v1", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("v2", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("x", new IntType()),
                new VariableDeclarationStatement("q", new IntType()),
                new HeapAllocationStatement("v1", new ValueExpression(new IntValue(20))),
                new HeapAllocationStatement("v2", new ValueExpression(new IntValue(30))),
                new NewLockStatement("x"),
                new ForkStatement(
                        buildProgram(
                                new ForkStatement(
                                        buildProgram(
                                                new LockStatement("x"),
                                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                                        new ReadHeapExpression(new VariableExpression("v1")),
                                                        new ValueExpression(new IntValue(1)),
                                                        BinaryExpression.OPERATION.SUBTRACTION
                                                )),
                                                new UnlockStatement("x")
                                         )
                                ),
                                new LockStatement("x"),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new UnlockStatement("x")
                        )
                ),
                new NewLockStatement("q"),
                new ForkStatement(
                        buildProgram(
                                new ForkStatement(
                                        buildProgram(
                                                new LockStatement("q"),
                                                new WriteHeapStatement("v2", new ArithmeticExpression(
                                                        new ReadHeapExpression(new VariableExpression("v2")),
                                                        new ValueExpression(new IntValue(5)),
                                                        BinaryExpression.OPERATION.ADDITION
                                                )),
                                                new UnlockStatement("q")
                                        )
                                ),
                                new LockStatement("q"),
                                new WriteHeapStatement("v2", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v2")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new UnlockStatement("q")
                        )
                ),
                new NopStatement(),
                new NopStatement(),
                new NopStatement(),
                new NopStatement(),
                new LockStatement("x"),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                new UnlockStatement("x"),
                new LockStatement("q"),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("v2"))),
                new UnlockStatement("q")
        );

        Statement programLatch = buildProgram(
                new VariableDeclarationStatement("v1", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("v2", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("v3", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("cnt", new IntType()),
                new HeapAllocationStatement("v1", new ValueExpression(new IntValue(2))),
                new HeapAllocationStatement("v2", new ValueExpression(new IntValue(3))),
                new HeapAllocationStatement("v3", new ValueExpression(new IntValue(4))),
                new NewLatchStatement("cnt", new ReadHeapExpression(new VariableExpression("v2"))),
                new ForkStatement(
                        buildProgram(
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                new CountdownStatement("cnt"),
                                new ForkStatement(
                                        buildProgram(
                                                new WriteHeapStatement("v2", new ArithmeticExpression(
                                                        new ReadHeapExpression(new VariableExpression("v2")),
                                                        new ValueExpression(new IntValue(10)),
                                                        BinaryExpression.OPERATION.MULTIPLICATION
                                                )),
                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v2"))),
                                                new CountdownStatement("cnt"),
                                                new ForkStatement(
                                                        buildProgram(
                                                                new WriteHeapStatement("v3", new ArithmeticExpression(
                                                                        new ReadHeapExpression(new VariableExpression("v3")),
                                                                        new ValueExpression(new IntValue(10)),
                                                                        BinaryExpression.OPERATION.MULTIPLICATION
                                                                )),
                                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v3"))),
                                                                new CountdownStatement("cnt")
                                                        )
                                                )
                                        )
                                )
                        )
                ),
                new AwaitStatement("cnt"),
                new PrintStatement(new ValueExpression(new IntValue(100))),
                new CountdownStatement("cnt"),
                new PrintStatement(new ValueExpression(new IntValue(100)))
        );

        Statement programToySemaphore = buildProgram(
                new VariableDeclarationStatement("v1", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("cnt", new IntType()),
                new HeapAllocationStatement("v1", new ValueExpression(new IntValue(2))),
                new NewToySemaphoreStatement("cnt",
                        new ReadHeapExpression(new VariableExpression("v1")),
                        new ValueExpression(new IntValue(1))),
                new ForkStatement(
                        buildProgram(
                                new ToyAcquireStatement("cnt"),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                new ToyReleaseStatement("cnt")
                        )
                ),
                new ForkStatement(
                        buildProgram(
                                new ToyAcquireStatement("cnt"),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(2)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                new ToyReleaseStatement("cnt")
                        )
                ),
                new ToyAcquireStatement("cnt"),
                new PrintStatement(new ArithmeticExpression(
                        new ReadHeapExpression(new VariableExpression("v1")),
                        new ValueExpression(new IntValue(1)),
                        BinaryExpression.OPERATION.SUBTRACTION
                )),
                new ToyReleaseStatement("cnt")

        );

        Statement programCountSemaphore = buildProgram(
                new VariableDeclarationStatement("v1", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("cnt", new IntType()),
                new HeapAllocationStatement("v1", new ValueExpression(new IntValue(1))),
                new NewCountSemaphoreStatement("cnt",
                        new ReadHeapExpression(new VariableExpression("v1"))),
                new ForkStatement(
                        buildProgram(
                                new CountAcquireStatement("cnt"),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                new CountReleaseStatement("cnt")
                        )
                ),
                new ForkStatement(
                        buildProgram(
                                new CountAcquireStatement("cnt"),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(2)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                new CountReleaseStatement("cnt")
                        )
                ),
                new CountAcquireStatement("cnt"),
                new PrintStatement(new ArithmeticExpression(
                        new ReadHeapExpression(new VariableExpression("v1")),
                        new ValueExpression(new IntValue(1)),
                        BinaryExpression.OPERATION.SUBTRACTION
                )),
                new CountReleaseStatement("cnt")

        );

        Statement programBarrier = buildProgram(
                new VariableDeclarationStatement("v1", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("v2", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("v3", new ReferenceType(new IntType())),
                new VariableDeclarationStatement("cnt", new IntType()),
                new HeapAllocationStatement("v1", new ValueExpression(new IntValue(2))),
                new HeapAllocationStatement("v2", new ValueExpression(new IntValue(3))),
                new HeapAllocationStatement("v3", new ValueExpression(new IntValue(4))),
                new NewBarrierStatement("cnt", new ReadHeapExpression(new VariableExpression("v2"))),
                new ForkStatement(
                        buildProgram(
                                new BarrierAwaitStatement("cnt"),
                                new WriteHeapStatement("v1", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v1")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1")))
                        )
                ),
                new ForkStatement(
                        buildProgram(
                                new BarrierAwaitStatement("cnt"),
                                new WriteHeapStatement("v2", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v2")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new WriteHeapStatement("v2", new ArithmeticExpression(
                                        new ReadHeapExpression(new VariableExpression("v2")),
                                        new ValueExpression(new IntValue(10)),
                                        BinaryExpression.OPERATION.MULTIPLICATION
                                )),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v2")))
                        )
                ),
                new BarrierAwaitStatement("cnt"),
                new PrintStatement(new ReadHeapExpression(new VariableExpression("v3")))
        );

        programs.add(program1);
        //programs.add(program2);
        //programs.add(program3);
        programs.add(program4);
        //programs.add(program5);
        //programs.add(program6);
        //programs.add(program7);
        programs.add(program8);
        programs.add(program9);
        programs.add(program10);
        programs.add(program11);
        programs.add(program12);
        programs.add(program13);
        programs.add(program14);
        programs.add(programSwitch);
        programs.add(programCondAssign);
        programs.add(programFor);
        programs.add(programRepeatUntil);
        programs.add(programSleep);
        programs.add(programSleep2);
        programs.add(programLock);
        programs.add(programLatch);
        programs.add(programToySemaphore);
        programs.add(programCountSemaphore);
        programs.add(programBarrier);
        return programs;
    }
}
