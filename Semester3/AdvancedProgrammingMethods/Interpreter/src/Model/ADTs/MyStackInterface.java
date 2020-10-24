package Model.ADTs;

import Exceptions.EmptyCollectionException;

public interface MyStackInterface<T> {
    T pop() throws EmptyCollectionException;
    void push(T elementToPush);
    boolean isEmpty();
}
