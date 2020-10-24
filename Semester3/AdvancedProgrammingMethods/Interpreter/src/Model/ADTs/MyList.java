package Model.ADTs;

import Exceptions.EmptyCollectionException;

import java.util.LinkedList;

public class MyList<T> implements MyListInterface<T>{
    LinkedList<T> listOfElements;

    public MyList(){
        this.listOfElements = new LinkedList<>();
    }
    public void add(T element){
        this.listOfElements.add(element);
    }

    public void insert(int position, T element){
        this.listOfElements.add(position, element);
    }

    public void remove(T element) throws EmptyCollectionException {
        if(this.listOfElements.isEmpty())
            throw new EmptyCollectionException("List is empty");
        this.listOfElements.remove(element);
    }

    public LinkedList<T> getElements(){
        return this.listOfElements;
    }

    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        for (T elem: listOfElements) {
            if (elem != null) {
                stringBuilder.append(elem.toString());
                stringBuilder.append("\n");
            }
        }
        return stringBuilder.toString();
    }

}
