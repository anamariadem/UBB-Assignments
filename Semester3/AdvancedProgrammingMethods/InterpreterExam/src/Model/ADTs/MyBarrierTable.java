package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class MyBarrierTable<V> implements MyBarrierTableInterface<V> {
    AtomicInteger address;
    Map<Integer, V> barrierTable;

    public MyBarrierTable() {
        address = new AtomicInteger(0);
        barrierTable = new HashMap<>();
    }

    public synchronized AtomicInteger allocate() throws InterpreterException {
        return new AtomicInteger(address.incrementAndGet());
    }

    public synchronized void add(Integer key, V value) {
        barrierTable.put(key, value);
    }

    public synchronized V getElementWithKey(Integer key) {
        return barrierTable.get(key);
    }

    public void remove(Integer key) throws InterpreterException {
        barrierTable.remove(key);
    }

    public synchronized void update(Integer key, V value) {
        barrierTable.put(key, value);
    }

    public Set<Integer> keySet() {
        return barrierTable.keySet();
    }

    public Map<Integer, V> getDictionary() {
        return barrierTable;
    }

    public synchronized boolean containsKey(Integer key) {
        return barrierTable.containsKey(key);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        for(Integer key: barrierTable.keySet()){
            stringBuilder.append(key.toString());
            stringBuilder.append("->");
            stringBuilder.append(barrierTable.get(key).toString());
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
