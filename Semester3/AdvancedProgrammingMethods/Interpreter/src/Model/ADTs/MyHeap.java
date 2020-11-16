package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class MyHeap<V> implements MyHeapInterface<V>{
    AtomicInteger address;
    MyDictionaryInterface<AtomicInteger, V> heap;

    public MyHeap() {
        address = new AtomicInteger(0);
        heap = new MyDictionary<>();
    }

    public AtomicInteger allocate() throws InterpreterException{
        return new AtomicInteger(address.incrementAndGet());
    }

    public void add(AtomicInteger key, V value) {
        heap.add(key, value);
    }

    public V getElementWithKey(AtomicInteger key){
        return heap.getElementWithKey(key);
    }
    public void remove(AtomicInteger key) throws InterpreterException{
        heap.remove(key);
    }
    public void update(AtomicInteger key, V value){
        heap.update(key, value);
    }
    public Set<AtomicInteger> keySet(){
        return heap.keySet();
    }
    public HashMap<AtomicInteger, V> getDictionary(){
        return heap.getDictionary();
    }
    public boolean containsKey(AtomicInteger key){
        return heap.containsKey(key);
    }

    public void setContent(Map<AtomicInteger, V> newContent) {
        heap.set(newContent);
    }

    public String toString() {
        return heap.toString();
    }
}
