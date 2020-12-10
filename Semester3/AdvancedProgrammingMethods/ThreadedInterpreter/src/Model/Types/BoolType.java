package Model.Types;
import Model.Values.BoolValue;
import Model.Values.Value;

public class BoolType implements Type {
    public boolean equals(Object anotherObject){
        return anotherObject instanceof BoolType;
    }

    public Value getDefault(){
        return new BoolValue(false);
    }

    public String toString(){
        return "boolean";
    }
}
