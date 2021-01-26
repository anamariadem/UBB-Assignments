package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class MyToySemaphoreTable<V> implements MyToySemaphoreTableInterface<V> {
    AtomicInteger address;
    Map<Integer, V> toySemaphoreTable;

    public MyToySemaphoreTable() {
        address = new AtomicInteger(0);
        toySemaphoreTable = new HashMap<>();
    }

    public synchronized AtomicInteger allocate() throws InterpreterException {
        return new AtomicInteger(address.incrementAndGet());
    }

    public synchronized void add(Integer key, V value) {
        toySemaphoreTable.put(key, value);
    }

    public synchronized V getElementWithKey(Integer key) {
        return toySemaphoreTable.get(key);
    }

    public void remove(Integer key) throws InterpreterException {
        toySemaphoreTable.remove(key);
    }

    public synchronized void update(Integer key, V value) {
        toySemaphoreTable.put(key, value);
    }

    public Set<Integer> keySet() {
        return toySemaphoreTable.keySet();
    }

    public Map<Integer, V> getDictionary() {
        return toySemaphoreTable;
    }

    public synchronized boolean containsKey(Integer key) {
        return toySemaphoreTable.containsKey(key);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        for(Integer key: toySemaphoreTable.keySet()){
            stringBuilder.append(key.toString());
            stringBuilder.append("->");
            stringBuilder.append(toySemaphoreTable.get(key).toString());
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
