CXX         = g++
CFLAGS      = -g -Wall
EXECUTABLES = executeit
USER_OBJS   = main.o FILI.o KILI.o PILI.o SILI.o YILI.o

all: $(EXECUTABLES)

$(EXECUTABLES): $(USER_OBJS)
	$(CXX) $(CFLAGS) $(USER_OBJS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f $(USER_OBJS) $(EXECUTABLES) output.*
