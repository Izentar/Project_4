CC=g++
KONF=-std=c++11

RELEASE: KONF+= -O2
RELEASE: project3.out

DEBUG: KONF+=-g -DDEBUG
DEBUG: project3.out

project3.out: main.cpp main_frame.cpp frame_inscription.cpp frame_fulfillment.cpp test_class.cpp
	$(CC) $(KONF) main.cpp main_frame.h main_frame.cpp main_frame_cast.cpp frame_inscription.h frame_inscription.cpp frame_fulfillment.h frame_fulfillment.cpp test_class.h test_class.cpp -o project3.out

clean:
	rm -rf *o project3.out
