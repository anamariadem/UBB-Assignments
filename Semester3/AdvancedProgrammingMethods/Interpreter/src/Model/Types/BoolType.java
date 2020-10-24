package Model.Types;

public class BoolType implements Type{
    public boolean equals(Object anotherObject){
        return anotherObject instanceof BoolType;
    }
    public String toString(){
        return "boolean";
    }
}
