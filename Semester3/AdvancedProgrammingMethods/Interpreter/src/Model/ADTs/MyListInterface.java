package Model.ADTs;

import Exceptions.EmptyCollectionException;
import Exceptions.InterpreterException;

import java.util.LinkedList;
import java.util.List;

public interface MyListInterface<T> {
    void add(T element);
    void insert(int position, T element);
    void remove(T element) throws InterpreterException;
    LinkedList<T> getElements();
}
