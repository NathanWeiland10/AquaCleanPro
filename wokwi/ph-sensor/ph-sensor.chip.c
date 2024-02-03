// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-License-Identifier: MIT

//pulling alot of this from this video ATM:
//https://youtu.be/yzdCS3A4DvU?si=FsRSPMh8JyQnX6t3

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // TODO: Put your chip variables here
  bool enabled;
  pin_t outpin;
  float value;
  
  float manual_value;
  string_t manual_value_attribute; 
} chip_state_t;

/* write the output to the outpin */
void update_output(chip_state_t * chip) {  
  float curVal = chip->value; 
  printf("Update chip output to %f\n", curVal);
  pin_dac_write(chip->outpin, curVal);
}

/* changes output pin to user set value */
void manual_value_changed(void* user_data) {
  chip_state_t* chip = (chip_state_t*)user_data;
  
  float curVal = attr_read_float(chip->manual_value_attribute);
  if (curVal != chip->manual_value) {
    chip->manual_value = curVal;
    chip->value = curVal;
    update_output(chip);
  }
}

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  
  // TODO: Initialize the chip, set up IO pins, create timers, etc.
  chip->value = 0.0;
  chip->outpin = pin_init("A", ANALOG);

  chip->manual_value_attribute =  attr_init_float("value", 2.5);

  const timer_config_t valuewatchtimerconf = {
    .callback = manual_value_changed,
    .user_data = chip,
  };
  timer_t valwatchtimer = timer_init(&valuewatchtimerconf);
  timer_start(valwatchtimer, 5000, true);

  printf("Hello from custom chip!\n");
}
