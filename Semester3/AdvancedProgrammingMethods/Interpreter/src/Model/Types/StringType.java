package Model.Types;
import Model.Values.StringValue;
import Model.Values.Value;

public class StringType implements Type{
    public boolean equals(Object anotherObject){
        return anotherObject instanceof StringType;
    }

    public Value getDefault(){
        return new StringValue("");
    }

    public String toString(){
        return "string";
    }
}
