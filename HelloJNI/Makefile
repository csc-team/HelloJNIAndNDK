ShowMessage.so:  ShowMessage.cpp  ShowMessage.h
	g++ -shared  -I/opt/java/32/jdk1.6.0_31/include -I/opt/java/32/jdk1.6.0_31/include/linux -o ShowMessage.so ShowMessage.cpp
ShowMessage.h: ShowMessage.class
	javah -jni ShowMessage
ShowMessage.class: ShowMessage.java
	javac ShowMessage.java

clear:
	rm ?*.so ?*.class ?*.h

