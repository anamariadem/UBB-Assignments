package Model.Types;

import Model.Values.ReferenceValue;
import Model.Values.Value;

import java.util.concurrent.atomic.AtomicInteger;

public class ReferenceType implements Type{
    Type inner;

    public ReferenceType(Type inner) {
        this.inner = inner;
    }

    public Type getInner() {
        return inner;
    }

    public Value getDefault() {
        return new ReferenceValue(new AtomicInteger(), inner);
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof ReferenceType)
            return inner.equals(((ReferenceType) obj).getInner());
        return false;
    }

    @Override
    public String toString() {
        return "ref " + inner.toString();
    }
}
