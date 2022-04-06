# F_JNI



## Introduction
***
The porpouse of this project is to get the concept of Java Native Interface (JNI), so that it starts with a basic 
example where Java calls a function in C++.

## Basic Structure
***
JAVA => JNI => C/C++

## Creating the Java Class
***
Let's start creating our first JNI program by implementing a classic “Hello World”.

To begin, we create the following Java class that includes the native method that will perform the work:

```
package jni;

public class jni.HelloWorld {
    // Load the library without "lib" either extension
    static {
        System.loadLibrary("native");
    }
    // Native method which is in C/C++ code
    private native void sayHello();

    public static void main(String[] args) {
        new jni.HelloWorld().sayHello();
    }
}
```
```
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
```
```
package jni;

public class UserData {
    // Load the library
    static {
        System.loadLibrary("libuserdata");
    }

    public static void main(String[] args) {
        UserData userData = new UserData();
        User user = userData.createUser("Flikendo", 26);
        userData.printData(user);
    }

    // Native method which is in C/C++ code
    public native User createUser(String name, int age);
    public native String printData(User user);
}
```

As we can see, we load the shared library in a static block. This ensures that it will be ready when we need it and from
wherever we need it.

Alternatively, in this trivial program, we could instead load the library just before calling our native method because 
we're not using the native library anywhere else.

## Implementing a Method in C++
***
Now, we need to create the implementation of our native method in C++.

Within C++ the definition and the implementation are usually stored in .h and .cpp files respectively.

First, to create the definition of the method, we have to use the -h flag of the Java compiler:

```
javac -h cpp/ jni/HelloWorld.java
```
```
javac -h cpp/ jni/Parameters.java
```
In the case that we want to pass a created class by own, we need to compile all those classes plus, the main class.
```
javac -h cpp/ jni/UserData.java
javac jni/User.java
```

This will generate a "java_HelloWorld.h" file with all the native methods included in the class passed as a parameter,
in this case, only one:

```
JNIEXPORT void JNICALL Java_java_jni_HelloWorld_sayHello (JNIEnv *, jobject);
```
```
JNIEXPORT jlong JNICALL Java_jni_Parameters_sumIntegers (JNIEnv *, jobject, jint, jint);
JNIEXPORT void JNICALL Java_jni_Parameters_isHigherThan (JNIEnv *, jobject, jint, jint);
```
```
JNIEXPORT jobject JNICALL Java_jni_UserData_createUser (JNIEnv *, jobject, jstring, jint);
JNIEXPORT jstring JNICALL Java_jni_UserData_printData (JNIEnv *, jobject, jobject);
```

As we can see, the function name is automatically generated using the fully qualified package, class and method name.

Also, something interesting that we can notice is that we're getting two parameters passed to our function; a pointer to
the current JNIEnv; and also the Java object that the method is attached to, the instance of our "main class".

Now, we have to create a new .cpp file for the implementation of the sayHello function. This is where we'll perform 
actions that print “Hello World” to console.

We'll name our .cpp file with the same name as the .h one containing the header and add this code to implement the 
native function:

```
#include "java_jni_HelloWorld.h"
#include <iostream>

// Function which is called from Java
JNIEXPORT void JNICALL Java_java_jni_HelloWorld_sayHello (JNIEnv *, jobject) {
    std::cout << "Hello from C++ !!" << std::endl;
}
```
```
#include "jni_Parameters.h"
#include <iostream>

using namespace std;

/*
 * Class:     jni_Parameters
 * Method:    sumIntegers
 * Signature: (II)I
 */
JNIEXPORT jlong JNICALL Java_jni_Parameters_sumIntegers (JNIEnv *env, jobject j_parameters, jint first_num,
                                                         jint second_num) {
    return (long)first_num + (long)second_num;
}

/*
 * Class:     jni_Parameters
 * Method:    isHigherThan
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jni_Parameters_isHigherThan (JNIEnv *env, jobject j_parameters, jint first_num,
                                                            jint second_num) {
    if (first_num < second_num) {
        cout << "Firts number is lower than the second number." << endl;
    } else {
        cout << "Second number is higher than the first number." << endl;
    }
}
```
```
#include "jni_UserData.h"
#include <iostream>

/*
 * Class:     jni_UserData
 * Method:    createUser
 * Signature: (Ljava/lang/String;I)Ljni/User;
 */
JNIEXPORT jobject JNICALL Java_jni_UserData_createUser (JNIEnv *env, jobject thisObject, jstring name, jint age) {
    // Create the object of the class UserData
    jclass j_cl = env -> FindClass("jni/User");
    jobject new_thisObject = env -> AllocObject(j_cl);

    // Get UserData fields to set
    jfield j_name = env -> GetFieldID(j_cl, "name", "Ljava/lang/String");
    jfield j_age = env -> GetFieldID(j_cl, "age", "I");

    // Set the values of the new object
    env -> SetObjectField(new_thisObject, j_name, name);
    env -> SetIntField(new_thisObject, j_age, age);

    // Set the values of the new object
    return new_thisObject;
}

/*
 * Class:     jni_UserData
 * Method:    printData
 * Signature: (Ljni/User;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_jni_UserData_printData (JNIEnv *env, jobject thisObject, jobject user) {
    jclass j_cl = env -> FindClass("jni/User");
    jmethodID j_method = env -> GetMethodID(j_cl, "printString", "()Ljava/lang/String");

    jstring result = (jstring)env -> CallObjectMethod(thisObject, j_method);

    return result;
}
```

## Compiling and Linking
***
Ubuntu version: 
```
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" jni_HelloWorld.cpp -o jni.HelloWorld.o
```

Windows version:
```
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" cpp/jni_HelloWorld.cpp -o cpp/jni_HelloWorld.o
```
```
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" cpp/jni_Parameters.cpp -o cpp/jni_Parameters.o
```
```
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" cpp/jni_UserData.cpp -o cpp/jni_UserData.o
```

Once we have the code compiled for our platform into the file jni.HelloWorld.o, we have to include it in a new shared 
library. Whatever we decide to name it is the argument passed into the method System.loadLibrary.

## Create the library
***
This command has to be executed from "lib/"!
Ubuntu version:
```
g++ -shared -fPIC -o libhelloworld.so ..cpp/jni_HelloWorld.o -lc
```

Windows version:
```
g++ -shared -o libhelloworld.dll ../cpp/jni_HelloWorld.o -Wl
g++ -shared -o libhelloworld.dll ../cpp/jni_HelloWorld.o -Wl,--add-stdcall-alias
```
```
g++ -shared -o libparameters.dll ../cpp/jni_Parameters.o -Wl
```
```
g++ -shared -o libuserdata.dll ../cpp/jni_UserData.o -Wl
```

## Important!
***
However, we need to add the full path to the directory containing the library we've just generated. This way Java will
know where to look for our native libs, the following command has to be executed from "src/"
```
java -cp . -Djava.library.path=lib/. jni.HelloWorld
```
```
java -cp . -Djava.library.path=lib/. jni.Parameters
```
```
java -cp . -Djava.library.path=lib/. jni.UserData
```


## Set up Intellij
***
In order to run the project with C++ libraries it has to be configured, so that go to Right Click in the project -> 
Open Module Settings -> Libraries -> Add new -> Java -> Select library path.