package jni;

public class UserData {
    static {
        System.loadLibrary("libuserdata");
    }

    // Load the library
    public static void main(String[] args) {
        UserData userData = new UserData();
        User user = userData.createUser("Flikendo", 26);
        System.out.println(userData.printData(user));
    }

    // Native method which is in C/C++ code
    public native User createUser(String name, int age);
    public native String printData(User user);
}
