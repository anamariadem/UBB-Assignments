package Model.Values;

import Model.Types.*;

public class IntValue implements Value{
    Integer value;

    public IntValue(int value){
        this.value = value;
    }

    public IntValue(){
        this.value = 0;
    }

    public int getValue(){
        return this.value;
    }

    public Type getType(){
        return new IntType();
    }

    public String toString(){
        return Integer.toString(value);
    }

    public boolean equals(Object object){
        if (this == object) return true;
        if (!(object instanceof IntValue))
            return false;
        IntValue objectAsIntValue = (IntValue) object;
        return value.equals(objectAsIntValue.value);
    }
}
