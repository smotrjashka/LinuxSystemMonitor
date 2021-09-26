#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>

using namespace std;

// Return the aggregate CPU utilization
float Processor::Utilization() {
    vector<string> cpu_info = LinuxParser::CpuUtilization();
    vector<int> cpu_ints;   ///user, nice, system, idle, iowait
                                ///irq, softirq, steal, gest, gest_nice

        for (string s : cpu_info)
        {
           cpu_ints.emplace_back(stoi(s));
        }
        int total, total_idle;
        total_idle = cpu_ints[3] + cpu_ints[4];
        for (size_t i = 0; i < 7; i++)
        {
            total += cpu_ints[i];
        }

        float utiliz;
        float total_idle_dif = (float)(total_idle - this->total_idle);
        float total_dif = (float)(total-this->total);
        utiliz = 1.0f - total_idle_dif/total_dif;

        this->total = total;
        this->total_idle = total_idle;

     return utiliz; 
     }