package Model.Values;

import Model.Types.BoolType;
import Model.Types.Type;

public class BoolValue implements Value {
    Boolean value;

    public BoolValue(boolean value){
        this.value = value;
    }

    public BoolValue(){
        this.value = false;
    }

    public boolean getValue(){
        return this.value;
    }

    public Type getType(){
        return new BoolType();
    }

    public String toString(){
        return Boolean.toString(value);
    }

    public boolean equals(Object object) {
        if (this == object) return true;
        if (!(object instanceof BoolValue))
            return false;
        BoolValue objectAsBoolValue = (BoolValue) object;
        return value.equals(objectAsBoolValue.value);
    }
}
