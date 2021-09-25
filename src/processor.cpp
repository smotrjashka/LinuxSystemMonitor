#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>

///#include <iostream> //for debug

using namespace std;

// Return the aggregate CPU utilization
float Processor::Utilization() {
    vector<string> cpu_info = LinuxParser::CpuUtilization();
    vector<int> cpu_ints;   ///user, nice, system, idle, iowait
                                ///irq, softirq, steal, gest, gest_nice

       // cout << "third=" << cpu_info[3];
      //  cout << "fourth" << cpu_info[4];
        for (string s : cpu_info)
        {
           cpu_ints.emplace_back(stoi(s));
        }
       // cout << "cpu length=" << cpu_ints.size();
        
        
      //  cout << "ints th=" << cpu_ints[3];
      //  cout << " ints fth=" << cpu_ints[4];
        int total, total_idle;
        total_idle = cpu_ints[3] + cpu_ints[4];
        for (size_t i = 0; i < 7; i++)
        {
            total += cpu_ints[i];
        }
      //  cout << "total " << total;
       // cout << "total idle " << total_idle ;
        float utiliz;
        float total_idle_dif = (float)(total_idle - this->total_idle);
        float total_dif = (float)(total-this->total);
     //   cout << "idel diff=" << total_idle_dif;
     //   cout << " total diff=" << total_dif;
        utiliz = 1.0f - total_idle_dif/total_dif;

      //  cout << "utiliz = " << utiliz << endl;
        this->total = total;
        this->total_idle = total_idle;

     return utiliz; 
     }