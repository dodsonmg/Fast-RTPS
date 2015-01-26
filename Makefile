BASEDIR=.
OUTDIR= $(BASEDIR)/output
CC= gcc
CPP= g++
LN= g++
AR=ar
CP=cp
LNK=ln



-include $(BASEDIR)/thirdparty/dev-env/building/makefiles/eProsima.mk
-include $(BASEDIR)/building/makefiles/fastrtps.mk

.PHONY: all

all: fastrtps

clean:
	@rm -f $(OBJS)
	@rm -f $(DEPS)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif
