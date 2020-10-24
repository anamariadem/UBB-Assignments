package Model.Types;

public class IntType implements Type{
    public boolean equals(Object anotherObject){
        return anotherObject instanceof IntType;
    }
    public String toString(){
        return "int";
    }
}
