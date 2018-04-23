import java.util.ArrayList;
import java.util.List;

class A {
    private B b;
    private int[] infoA = new int[10000];

    public void refB(B b) {
        this.b = b;
    }
}

class B {
    private int[] infoB = new int[10000];
  	private A a;

    public void refA(A a) {
        this.a = a;
    }
}
