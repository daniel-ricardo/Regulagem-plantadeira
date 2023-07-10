PROJECT=Regulagem
CC=javac
CCFLAGS=
RUN=java

all:Regulagem.class Window.class
	$(CC) Main.java
	$(RUN) Main

Regulagem.class:Regulagem.java
	$(CC) Regulagem.java

Window.class:Window.java
	$(CC) Window.java

testRegulagem:Regulagem.class
	$(RUN) Regulagem

testWindow:Regulagem.class Window.class
	$(RUN) Window
