package Model.Statements;

import Exceptions.*;
import Model.ProgramState;

public interface Statement {
    ProgramState execute(ProgramState state) throws InterpreterException;
}
