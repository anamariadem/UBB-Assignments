package Model.Types;

import Model.Values.IntValue;
import Model.Values.Value;

public class IntType implements Type {
    public boolean equals(Object anotherObject){
        return anotherObject instanceof IntType;
    }

    public Value getDefault(){
        return new IntValue(0);
    }

    public String toString(){
        return "int";
    }
}
