#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void
print_usage()
{

   printf("gpioctl dirin|dirout|get|set|clear gpio\n");

}

void getGPIOname(int gpio_pin, char *gpio_name)
{
	if (gpio_pin <= 31)
		sprintf(gpio_name, "pioA%d", gpio_pin);
	else if (gpio_pin >= 32 && gpio_pin <= 63)
		sprintf(gpio_name, "pioB%d", (gpio_pin-32));
	else if (gpio_pin >= 64 && gpio_pin <= 95)
		sprintf(gpio_name, "pioC%d", (gpio_pin-64));
	else
		sprintf(gpio_name, "pioD%d", (gpio_pin-96));
}
 
void exportGPIO(int gpio_pin, int mode)
{
	int fd;
	FILE *fp;
	char path[64];
		
	if (mode == 1)
		sprintf(path, "/sys/class/gpio/export");
	else
		sprintf(path, "/sys/class/gpio/unexport");

	fd = open(path, O_WRONLY);
	if (fd < 0)
		perror("Failed to open export");

	fp = fdopen(fd, "w");
	if (fp == NULL)
		perror("export gpio failed");
	else
		fprintf(fp,"%d",gpio_pin);
	fclose(fp);
}
 
int setdirGPIO(char *gpio_name,char *direction)
{
    int fd;
    char path[64];
    FILE *fp;

    sprintf(path,"/sys/class/gpio/%s/direction", gpio_name);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
	perror("Failed to open direction");
	return -1;
    }

    fp = fdopen(fd, "w");
    if (fp == NULL) {
        perror("direction open failed");
	return -1;
    }
    else {
	if (!strcmp("dirin", direction))
	    fprintf(fp,"in");
	else
	    fprintf(fp, "out");
    }
    fclose(fp);
    return 0;
    
} 
 
int getGPIOvalue(char *gpio_name)
{
    char path[64];
    char value_str[3];
    int fd;
 
    sprintf(path, "/sys/class/gpio/%s/value", gpio_name);
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open gpio value for reading!");
        return -1;
    }
 
    if (read(fd, value_str, 3) < 0) {
        perror("Failed to read value!");
        return -1;
    }
 
    close(fd);
    return (atoi(value_str));
}

int setGPIOvalue(char *gpio_name, int value)
{
	char path[64], value_str[4];
	int fd;
	FILE *fp;
	
	sprintf(path, "/sys/class/gpio/%s/direction", gpio_name);
	fd = open(path, O_RDONLY);
	
	if (read(fd, value_str, 3) < 0) {
		perror("Failed to read direction value!");
		return -1;
	}
	close(fd);
	
	if (!strcmp("in", value_str)) {
		perror("Failed to set value because of in direction");
		return -1;
	}

	sprintf(path, "/sys/class/gpio/%s/value", gpio_name);
	fd = open(path, O_RDWR);
	if (fd < 0) {
	    perror("Failed to open gpio value for reading!");
	    return -1;
	}
	
	fp = fdopen(fd, "w");
	if (fp == NULL)
		perror("value open failed");
	else
		fprintf(fp, "%d", value);
	fclose(fp);

	return 0;
}
 

int main(int argc, char **argv)
{
	int gpio_pin, result = -1;
	char gpio_name[16];

	if (argc != 3)
	{
		print_usage();
		return -1;
	}

	gpio_pin = atoi(argv[2]);

	exportGPIO(gpio_pin, 1);
	getGPIOname(gpio_pin, gpio_name);

	if (!strcmp("dirin", argv[1]) || !strcmp("dirout", argv[1])) {
		result = setdirGPIO(gpio_name, argv[1]);
	} else if (!strcmp("get", argv[1])) {
		result = getGPIOvalue(gpio_name);
	} else if (!strcmp("set", argv[1])) {
		result = setGPIOvalue(gpio_name, 1);
	} else if (!strcmp("clear", argv[1])) {
		result = setGPIOvalue(gpio_name, 0);
	} else {
		perror("Wrong command!\n");
	}
	//Guider
	printf("%d\n", result);

	exportGPIO(gpio_pin, 0);

    return result;
}

