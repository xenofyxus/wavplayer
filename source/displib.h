#include <pic32mx.h>
#include <stdint.h>

#ifndef DISPLIB_H
#define DISPLIB_H

void display_init();
void display_string(int line,char *str);
void display_image(int startline, const uint8_t *img);
void display_update();

#endif