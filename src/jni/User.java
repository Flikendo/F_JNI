package jni;

public class User {
    public String name;
    public double balance;

    public String getUserInfo() {
        return "[name]=" + name + ", [balance]=" + balance;
    }
}
