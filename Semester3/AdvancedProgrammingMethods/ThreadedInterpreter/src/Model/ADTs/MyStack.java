package Model.ADTs;


import Exceptions.InterpreterException;

import java.util.Stack;

public class MyStack<T> implements MyStackInterface<T> {
    Stack<T> stack;

    public MyStack(){
        this.stack = new Stack<T>();
    }

    public T pop() throws InterpreterException {
        if(this.stack.empty())
            throw new InterpreterException("Stack is empty");
        return this.stack.pop();
    }
    public void push(T elementToPush){
        this.stack.push(elementToPush);
    }

    public boolean isEmpty(){
        return this.stack.empty();
    }

    public T top() throws InterpreterException {
        if(stack.empty())
            throw new InterpreterException("Stack is empty");
        return stack.peek();
    }

    public String toString() {
        return stack.toString();
    }

}
