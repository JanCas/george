#include "MMQueue.hpp"

MMQueue::MMQueue(int max_queue_size, const uint8_t sensor_pins[], int emitter_pin){
    this->max_queue_size = max_queue_size;

    qtr_sensor->setTypeRC();
    qtr_sensor->setSensorPins(sensor_pins, sizeof(sensor_pins)/sizeof(uint8_t));
    qtr_sensor->setEmitterPin(emitter_pin);
    num_sensors = sizeof(sensor_pins) / sizeof(uint8_t);
    sensor_values = new uint16_t[num_sensors];
}

MMQueue::~MMQueue(){
    delete qtr_sensor;
}

bool MMQueue::is_full(){
    return num_mm_in_queue() > max_queue_size;
}

int MMQueue::num_mm_in_queue(){
    // read raw sensor values
  qtr_sensor->read(sensor_values);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  int count_below_1000 = 0;
  
  for (uint8_t i = 0; i < num_sensors; i++)
  {
      if (sensor_values[i] < 1000) count_below_1000++;
  }

  return round((float)(count_below_1000) / .615);
}