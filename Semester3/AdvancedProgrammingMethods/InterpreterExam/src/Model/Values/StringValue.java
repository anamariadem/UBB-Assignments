package Model.Values;

import Model.Types.StringType;
import Model.Types.Type;

public class StringValue implements Value {
    String value;

    public StringValue(String value){
        this.value = value;
    }

    public String getValue(){
        return value;
    }

    public Type getType(){
        return  new StringType();
    }

    public String toString(){
        return value.toString();
    }

    public boolean equals(Object object){
        if (this == object) return true;
        if (!(object instanceof StringValue))
            return false;
        StringValue objectAsStringValue = (StringValue) object;
        return value.equals(objectAsStringValue.getValue());
    }
}
