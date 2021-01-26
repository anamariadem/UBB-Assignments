package Model;

public class Tuple<A, B> {
    A first;
    B second;

    public Tuple(A first, B second) {
        this.first = first;
        this.second = second;
    }

    public A getFirst() {
        return first;
    }

    public B getSecond() {
        return second;
    }

    @Override
    public String toString() {
        return first.toString() + ", " + second.toString();
    }
}
