#include "MMQueue.hpp"

MMQueue::MMQueue(const uint8_t sensor_pins[], int emitter_pin)
{
  this->sensor_pins = sensor_pins;
  this->emitter_pin = emitter_pin;
  this->qtr_sensor = new QTRSensors();
}

MMQueue::~MMQueue()
{
  delete qtr_sensor;
}

void MMQueue::init()
{

  qtr_sensor->setTypeRC();
  qtr_sensor->setSensorPins(sensor_pins, 13);
  qtr_sensor->setEmitterPin(emitter_pin);
  // num_sensors = sizeof(sensor_pins) / sizeof(uint8_t);
  num_sensors = 13;
  // sensor_values = new uint16_t[num_sensors];
}

double MMQueue::num_mm_in_queue()
{
  qtr_sensor->read(sensor_values);

  int count_below_threshold = 0;

  for (uint8_t i = 0; i < 13; i++)
  {
    // Serial.print(sensor_values[i]);
    // Serial.print('\t');
    if (sensor_values[i] < 350) {
      count_below_threshold++;
    }
  }


  double num_unrounded = (float)(count_below_threshold) / 1.6;
  return round(num_unrounded);
}