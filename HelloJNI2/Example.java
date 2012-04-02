import java.io.File;

public class Example {
    int i;

    public static void main(String args[]) {
        Example ex = new Example();
        ex.i = 28;
        System.out.println("Before native method call.");
        int result = ex.nativeMethod();
        System.out.println("After native method call.");
        System.out.println("Result = " + result);
    }

    public void printMessage() {
        System.out.println("This method was called from native method.");
    }

    public native int nativeMethod();

    static {
        System.load(new File("Example.so").getAbsolutePath());
    }
}
