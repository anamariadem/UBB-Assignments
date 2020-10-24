package Model.ADTs;


import Exceptions.EmptyCollectionException;

import java.util.EmptyStackException;
import java.util.Enumeration;
import java.util.HashMap;

public interface MyDictionaryInterface<K, V> {
    void add(K key, V value);
    V getElementWithKey(K key);
    void remove(K key) throws EmptyCollectionException;
    void update(K key, V value);
    HashMap<K, V> getDictionary();
    boolean isVariableDefined(K key);
}
