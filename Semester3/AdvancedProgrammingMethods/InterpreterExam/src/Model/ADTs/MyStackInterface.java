package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.Stack;

public interface MyStackInterface<T> {
    T pop() throws InterpreterException;
    void push(T elementToPush);
    boolean isEmpty();
    T top() throws InterpreterException;
    Stack<T> getStackContent();
}
