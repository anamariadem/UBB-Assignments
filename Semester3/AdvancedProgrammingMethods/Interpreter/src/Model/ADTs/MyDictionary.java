package Model.ADTs;

import Exceptions.InterpreterException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

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

    public void set(Map<K, V> newContent) {
        dictionary.clear();
        for (K i : newContent.keySet()) {
            dictionary.put(i, newContent.get(i));
        }
    }

    public Set<K> keySet() {
        return dictionary.keySet();
    }

    public void remove(K key) throws InterpreterException {
        if(this.dictionary.isEmpty())
            throw new InterpreterException("Dictionary is empty");
        this.dictionary.remove(key);
    }

    public boolean containsKey(K key){
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
