package jni;

public class HelloWorld {
    // Load the library
    static {
        System.loadLibrary("libhelloworld");
    }
    // Native method which is in C/C++ code
    private native void sayHello();

    public static void main(String[] args) {
        new HelloWorld().sayHello();
    }
}
