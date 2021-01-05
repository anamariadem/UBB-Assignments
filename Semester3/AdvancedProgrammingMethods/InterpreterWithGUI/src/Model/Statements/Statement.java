package Model.Statements;

import Exceptions.*;
import Model.ADTs.MyDictionaryInterface;
import Model.ProgramState;
import Model.Types.Type;

public interface Statement {
    ProgramState execute(ProgramState state) throws InterpreterException;
    MyDictionaryInterface<String, Type> typeCheck (MyDictionaryInterface<String, Type> variableTypes) throws InterpreterException;
}
