package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class MyCountSemaphoreTable<V> implements MyCountSemaphoreTableInterface<V> {
    AtomicInteger address;
    Map<Integer, V> countSemaphoreTable;

    public MyCountSemaphoreTable() {
        address = new AtomicInteger(0);
        countSemaphoreTable = new HashMap<>();
    }

    public synchronized AtomicInteger allocate() throws InterpreterException {
        return new AtomicInteger(address.incrementAndGet());
    }

    public synchronized void add(Integer key, V value) {
        countSemaphoreTable.put(key, value);
    }

    public synchronized V getElementWithKey(Integer key) {
        return countSemaphoreTable.get(key);
    }

    public void remove(Integer key) throws InterpreterException {
        countSemaphoreTable.remove(key);
    }

    public synchronized void update(Integer key, V value) {
        countSemaphoreTable.put(key, value);
    }

    public Set<Integer> keySet() {
        return countSemaphoreTable.keySet();
    }

    public Map<Integer, V> getDictionary() {
        return countSemaphoreTable;
    }

    public synchronized boolean containsKey(Integer key) {
        return countSemaphoreTable.containsKey(key);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        for(Integer key: countSemaphoreTable.keySet()){
            stringBuilder.append(key.toString());
            stringBuilder.append("->");
            stringBuilder.append(countSemaphoreTable.get(key).toString());
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
