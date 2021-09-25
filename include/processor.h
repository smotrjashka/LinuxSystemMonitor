#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // Declare any necessary private members
 private:
    int total = 0;
    int total_idle = 0;
};

#endif