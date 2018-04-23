import java.util.ArrayList;
import java.util.List;
import org.math.plot.*;

public class PerformanceTest {
  	public static void test(){
        A A_test = new A();
        B B_test = new B();

        A_test.refB(B_test);
        B_test.refA(A_test);
     }

    public static void main(String[] args) {
      	// Get the Java runtime
 		Runtime runtime = Runtime.getRuntime();
      	long memory_free_0 = runtime.freeMemory();
        test();
        long memory_used_0 = memory_free_0 - runtime.freeMemory();
        System.out.println("Used memory is kb: " + memory_used_0 / 1024.0);

        int n_test = 50;
      	long memory_free_1 = runtime.freeMemory();
        for (int i = 0; i <= n_test; i++) {
            test();
        }
        long memory_used_1 = memory_free_1 - runtime.freeMemory();
        System.out.println("Used memory is kb: " + memory_used_1 / 1024.0);

        Plot plot = Plot.plot(null).
            series(null, Plot.data().
                    xy(1, 2).
                    xy(3, 4), null);

// saving sample_minimal.png
plot.save("sample_minimal", "png");
    }
}
