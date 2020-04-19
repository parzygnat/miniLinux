#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <gpiod.h>
#define NUM_OF_LEDS 4

int buttonPress(int* output, int number) {
    char *chipname = "gpiochip1";
    struct gpiod_chip *chip;
    int ret;
    struct gpiod_line_bulk lines;
    struct gpiod_line_bulk event_lines;
    struct gpiod_line *line;
    struct gpiod_line_event event;
    unsigned int event_size;
    unsigned int line_nums[] = {12, 13, 14, 15};
	int* length_array = malloc(sizeof(int)*4);
	unsigned int length;
    int i = 0;
    struct timespec ts = {10, 0};
    struct timespec t = {0, 0};
    struct timeval previous, current;
    gettimeofday(&previous, NULL);
    bool bnc_flag = false;
    int bnc_count = 0;
    chip = gpiod_chip_open_by_name(chipname);
    if (!chip)
    {
        perror("Open chip failed\n");
        return -1;
    }
    ret = gpiod_chip_get_lines(chip, line_nums, NUM_OF_LEDS, &lines);
    if (ret < 0)
    {
        perror("Get lines failed\n");
        gpiod_line_release_bulk(&lines);
        gpiod_chip_close(chip);
        return -1;
    }

    while(i < number) {

        ret = gpiod_line_request_bulk_falling_edge_events(&lines, "button_click");
        if (ret < 0)
        {
            perror("Request falling edge event failed!\n");
            gpiod_line_release_bulk(&lines);
            gpiod_chip_close(chip);
            return -1;
        }

        ret = gpiod_line_event_wait_bulk(&lines, &ts, &event_lines);
        if (ret < 0 || ret == 0)
            {
                perror("Wait failed!");
                gpiod_line_release_bulk(&lines);
                gpiod_chip_close(chip);
                return -1;
            }
        gettimeofday(&current, NULL);
        if((current.tv_sec - previous.tv_sec) * 1000000 + current.tv_usec - previous.tv_usec < 250000) {
            gpiod_line_release_bulk(&lines);
            previous = current;
            continue;
        }
        previous = current;
        line = gpiod_line_bulk_get_line(&event_lines, 0);
        length = gpiod_line_offset(line);
        output[i] = length - 11;
        printf("You've entered %d\n", output[i]);
        ++i;
        gpiod_line_release_bulk(&lines);
    }
    gpiod_line_release_bulk(&lines);
    gpiod_chip_close(chip);
    return 0;
}