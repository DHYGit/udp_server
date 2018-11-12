target:=udp_server

SRCS:=main.cpp

OBJS=$(SRCS:%.cpp=%.o)

CPP = g++

all:$(target)

$(target):$(OBJS)
	@echo "Linking $@"
	$(CPP) $< -o $@
$(OBJS):$(SRCS)
	@echo "Compling $<"
	$(CPP) -c $<
.PHONY:clean
clean:
	rm -f $(target)
	rm -f $(OBJS)
