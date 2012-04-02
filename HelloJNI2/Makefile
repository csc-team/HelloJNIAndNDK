Example.so:  Example.cpp  Example.h
	g++ -shared  -I/opt/java/32/jdk1.6.0_31/include -I/opt/java/32/jdk1.6.0_31/include/linux -o Example.so Example.cpp
Example.h: Example.class
	javah -jni Example
Example.class: Example.java
	javac Example.java

clear:
	rm ?*.class ?*.so ?*.h
