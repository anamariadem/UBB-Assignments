package Model.ADTs;


import Exceptions.EmptyCollectionException;

import java.util.Stack;

public class MyStack<T> implements MyStackInterface<T>{
    Stack<T> stack;

    public MyStack(){
        this.stack = new Stack<T>();
    }

    public T pop() throws EmptyCollectionException {
        if(this.stack.empty())
            throw new EmptyCollectionException("Stack is empty");
        return this.stack.pop();
    }
    public void push(T elementToPush){
        this.stack.push(elementToPush);
    }

    public boolean isEmpty(){
        return this.stack.empty();
    }

    public String toString() {
        return stack.toString();
    }

}
