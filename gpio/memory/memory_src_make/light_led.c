#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int light_led(int number)
{
    char *chipname = "gpiochip1";
	struct gpiod_chip *chip;
	int i, j, ret;

	struct gpiod_line_bulk lines;
	unsigned int line_nums[]={24,25,26,27};
	unsigned int line_len=4;
	int vals[4]={0,0,0,0};


	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		perror("Open chip failed\n");
		return -1;
	}
	
	ret=gpiod_chip_get_lines(chip,line_nums,line_len,&lines);
	if (ret < 0) {
		perror("Get lines failed\n");
		gpiod_chip_close(chip);
		return -1;
	}


	ret=gpiod_line_request_bulk_output(&lines,"led_blink",vals);
	if (ret < 0) {
		perror("Request line as output failed\n");
		gpiod_line_release_bulk(&lines);
		gpiod_chip_close(chip);
		return -1;
	}

    ret = gpiod_line_set_value_bulk(&lines, vals);
    if (ret < 0) {
        perror("Set line output failed\n");
        gpiod_line_release_bulk(&lines);
        gpiod_chip_close(chip);
        return -1;
    }
    for(int i = 0; i < number; ++i) vals[i] = 1;
    ret = gpiod_line_set_value_bulk(&lines, vals);
    if (ret < 0) {
        perror("Set line output failed\n");
        gpiod_line_release_bulk(&lines);
        gpiod_chip_close(chip);
        return -1;
    }


	gpiod_line_release_bulk(&lines);
	gpiod_chip_close(chip);
}