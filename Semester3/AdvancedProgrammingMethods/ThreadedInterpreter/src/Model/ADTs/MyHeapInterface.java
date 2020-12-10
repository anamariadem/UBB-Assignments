package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public interface MyHeapInterface<V> {
    AtomicInteger allocate() throws InterpreterException;
    void add(AtomicInteger key, V value);
    V getElementWithKey(AtomicInteger key);
    void remove(AtomicInteger key) throws InterpreterException;
    void update(AtomicInteger key, V value);
    Set<AtomicInteger> keySet();
    HashMap<AtomicInteger, V> getDictionary();
    boolean containsKey(AtomicInteger key);
    void setContent(Map<AtomicInteger, V> newContent);
}
