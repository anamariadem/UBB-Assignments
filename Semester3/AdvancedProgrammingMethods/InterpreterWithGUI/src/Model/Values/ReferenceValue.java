package Model.Values;

import Model.Types.ReferenceType;
import Model.Types.Type;

import java.util.concurrent.atomic.AtomicInteger;

public class ReferenceValue implements Value {
    AtomicInteger address;
    Type locationType;

    public ReferenceValue(AtomicInteger address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public AtomicInteger getAddress() {
        return address;
    }

    public Type getLocationType() {
        return locationType;
    }

    public Type getType() {
        return new ReferenceType(locationType);
    }

    public String toString() {
        return address + " -> " + locationType.toString();
    }
}
