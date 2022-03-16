#include "MMQueue.hpp"

MMQueue::MMQueue(int max_queue_size, const uint8_t sensor_pins[], int emitter_pin)
{
  this->max_queue_size = max_queue_size;
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

bool MMQueue::is_full()
{
  return num_mm_in_queue() > max_queue_size;
}

double MMQueue::num_mm_in_queue()
{
  qtr_sensor->read(sensor_values);

  int count_below_threshold = 0;

  for (uint8_t i = 0; i < 13; i++)
  {
    if (sensor_values[i] < 600) {
      count_below_threshold++;
    }
  }

  double num_unrounded = (float)(count_below_threshold) / 1.8;
  return num_unrounded == 0 ? 0.0 : floor(num_unrounded) + 1;
}