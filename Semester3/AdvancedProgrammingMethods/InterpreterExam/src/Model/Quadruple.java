package Model;

public class Quadruple<A, B, C, D> {
    A first;
    B second;
    C third;
    D fourth;

    public Quadruple(A first, B second, C third, D fourth) {
        this.first = first;
        this.second = second;
        this.third = third;
        this.fourth = fourth;
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

    public D getFourth() {
        return fourth;
    }

    @Override
    public String toString() {
        return first.toString() + ", " + second.toString() + ", " + third.toString() + ", " + fourth.toString();
    }
}
