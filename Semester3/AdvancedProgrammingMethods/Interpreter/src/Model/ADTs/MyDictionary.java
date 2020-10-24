package Model.ADTs;

import Exceptions.EmptyCollectionException;

import java.util.Dictionary;
import java.util.Enumeration;
import java.util.HashMap;

public class MyDictionary<K,V> implements MyDictionaryInterface<K,V> {
    HashMap<K,V> dictionary;

    public MyDictionary(){
        this.dictionary = new HashMap<>();
    }

    public void add(K key, V value){
        this.dictionary.put(key, value);
    }

    public V getElementWithKey(K key){
        return this.dictionary.get(key);
    }


    public void remove(K key) throws EmptyCollectionException {
        if(this.dictionary.isEmpty())
            throw new EmptyCollectionException("Dictionary is empty");
        this.dictionary.remove(key);
    }

    public boolean isVariableDefined(K key){
        return this.dictionary.containsKey(key);
    }

    public void update(K key, V value){
        this.dictionary.replace(key, value);
    }

    public HashMap<K, V> getDictionary(){
        return this.dictionary;
    }

    public String toString(){
        StringBuilder stringBuilder = new StringBuilder();
        for(K key: dictionary.keySet()){
            stringBuilder.append(key.toString());
            stringBuilder.append("->");
            stringBuilder.append(dictionary.get(key).toString());
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
