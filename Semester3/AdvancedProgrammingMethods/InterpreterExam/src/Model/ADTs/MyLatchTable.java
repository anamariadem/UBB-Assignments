package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class MyLatchTable<V> implements MyLatchTableInterface<V> {
    AtomicInteger address;
    Map<Integer, V> latchTable;

    public MyLatchTable() {
        address = new AtomicInteger(0);
        latchTable = new HashMap<>();
    }

    public synchronized AtomicInteger allocate() throws InterpreterException {
        return new AtomicInteger(address.incrementAndGet());
    }

    public synchronized void add(Integer key, V value) {
        latchTable.put(key, value);
    }

    public synchronized V getElementWithKey(Integer key) {
        return latchTable.get(key);
    }

    public void remove(Integer key) throws InterpreterException {
        latchTable.remove(key);
    }

    public synchronized void update(Integer key, V value) {
        latchTable.put(key, value);
    }

    public Set<Integer> keySet() {
        return latchTable.keySet();
    }

    public Map<Integer, V> getDictionary() {
        return latchTable;
    }

    public synchronized boolean containsKey(Integer key) {
        return latchTable.containsKey(key);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        for(Integer key: latchTable.keySet()){
            stringBuilder.append(key.toString());
            stringBuilder.append("->");
            stringBuilder.append(latchTable.get(key).toString());
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
