CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Player.o Transporter.o Ladder.o Chute.o Field.o ChutesAndLadders.o    

LIBS =

TARGET =	ChutesAndLadders

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
