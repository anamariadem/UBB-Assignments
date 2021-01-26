package Model;

public class Triplet<A, B, C> {
    A first;
    B second;
    C third;

    public Triplet(A first, B second, C third) {
        this.first = first;
        this.second = second;
        this.third = third;
    }

    public A getFirst() {
        return first;
    }

    public B getSecond() {
        return second;
    }

    public C getThird() {
        return third;
    }

    @Override
    public String toString() {
        return first.toString() + ", " + second.toString() + ", " + third.toString();
    }
}
