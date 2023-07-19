#CC = /home/david/WORK_PATH/openwrt_test/test/svn/trunk/upload/svn/trunk/staging_dir/toolchain-arm_cortex-a9+vfpv3_gcc-4.8-linaro_uClibc-0.9.33.2_eabi/bin/arm-openwrt-linux-gcc
TARGET = gpioctl

LINK = -lrt -lm

#CFLAGS = -O0 -fPIC

OBJFILE = gpioctl.o
#CC = $(TARGET_CC)
#vpath %.c advantech

all: $(TARGET)
$(TARGET): $(OBJFILE)
	$(TARGET_CC) $(CFLAGS) $(LIBS) -o $(TARGET) $(OBJFILE) $(LINK)


%.o: %.c
	$(TARGET_CC) $(CFLAGS) -w -c $<
clean:
	rm -rf *.o $(TARGET)
