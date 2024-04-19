#define DEBUG 1

#include <Arduino.h>

uint8_t input_pins[]={A0,A1,A2,A3,A4};
uint16_t thresholds_values[]={200,200,200,200,200};

uint8_t last_page = 0;
uint8_t reading_count =100;

void check_page_number()
{
  uint8_t current_page =0;
  uint16_t max_values[sizeof(input_pins)]={0};
  uint16_t values_readed[sizeof(input_pins)]={0};
  for(uint8_t i=0; i<reading_count; i++)
  {
    for(uint8_t j=0; j<sizeof(input_pins); j++)
    {
      values_readed[j]= analogRead(input_pins[j]);
      if(values_readed[j] >  max_values[j]) {max_values[j] = values_readed[j]; }
    }
  }
  for(uint8_t i=0; i<sizeof(input_pins); i++)
  {
    if(DEBUG){Serial.print(max_values[i]); Serial.print("\t");}
    if(max_values[i] > thresholds_values[i]){current_page = i; current_page+=1;}
  }
  if(DEBUG){Serial.println(" ");}
  if(current_page != last_page){ last_page = current_page; Serial.println(current_page); }
}

void setup() {
Serial.begin(9600);
Serial.setTimeout(5);
delay(100);
}

void loop() {
 check_page_number();
}
