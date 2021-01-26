package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class MyLockTable<V> implements MyLockTableInterface<V> {
    AtomicInteger address;
    Map<Integer, V> lockTable;

    public MyLockTable() {
        address = new AtomicInteger(0);
        lockTable = new HashMap<>();
    }

    public synchronized AtomicInteger allocate() throws InterpreterException {
        return new AtomicInteger(address.incrementAndGet());
    }

    public synchronized void add(Integer key, V value) {
        lockTable.put(key, value);
    }

    public synchronized V getElementWithKey(Integer key) {
        return lockTable.get(key);
    }

    public void remove(Integer key) throws InterpreterException {
        lockTable.remove(key);
    }

    public synchronized void update(Integer key, V value) {
        lockTable.put(key, value);
    }

    public Set<Integer> keySet() {
        return lockTable.keySet();
    }

    public Map<Integer, V> getDictionary() {
        return lockTable;
    }

    public synchronized boolean containsKey(Integer key) {
        return lockTable.containsKey(key);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        for(Integer key: lockTable.keySet()){
            stringBuilder.append(key.toString());
            stringBuilder.append("->");
            stringBuilder.append(lockTable.get(key).toString());
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
