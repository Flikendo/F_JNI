package jni;

public class Parameters {
    // Load the library
    static {
        System.loadLibrary("libparameters");
    }

    public static void main(String[] args) {
        System.out.println(new Parameters().sumIntegers(8, 7));
        new Parameters().isHigherThan(3, 2);
    }

    // Native method which is in C/C++ code
    private native long sumIntegers(int firstNum, int secondNum);
    private native void isHigherThan(int firstNum, int secondNum);
}
