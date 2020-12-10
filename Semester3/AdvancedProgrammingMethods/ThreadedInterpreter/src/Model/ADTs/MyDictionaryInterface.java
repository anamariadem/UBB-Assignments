package Model.ADTs;


import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public interface MyDictionaryInterface<K, V> {
    void add(K key, V value);
    V getElementWithKey(K key);
    void set(Map<K, V> dictionary);
    void remove(K key) throws InterpreterException;
    void update(K key, V value);
    Set<K> keySet();
    HashMap<K, V> getDictionary();
    boolean containsKey(K key);
    MyDictionaryInterface<K, V> createCopy();
}
