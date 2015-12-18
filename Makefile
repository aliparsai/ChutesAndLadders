CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		ShootsAndLadders.o Field.o Ladder.o Shoot.o Player.o Transporter.o 

LIBS =

TARGET =	ShootsAndLadders

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
