package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.LinkedList;

public interface MyListInterface<T> {
    void add(T element);
    void insert(int position, T element);
    void remove(T element) throws InterpreterException;
    LinkedList<T> getElements();
}
