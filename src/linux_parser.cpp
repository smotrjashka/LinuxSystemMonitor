#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::map;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  unsigned long mem_total, mem_free, mem_avail, buffered_mem;
  std::ifstream file(kProcDirectory + kMeminfoFilename);
  if(file.is_open()){
      string line, str, value, last;
      map<string, unsigned long> mem_info_map;
      mem_info_map.insert(std::make_pair("MemTotal:", 0));
      mem_info_map.insert(std::make_pair("MemFree:", 0));
      mem_info_map.insert(std::make_pair("MemAvailable:", 0));
      mem_info_map.insert(std::make_pair("Buffers:", 0));
      int count = 0;
      while (std::getline(file, line) && count < 4)
      {
        std::istringstream istrstrm(line);
        while (istrstrm >> str >> value >> last)
        {
        std::map<string, unsigned long>::iterator it = mem_info_map.find(str);
         if(it != mem_info_map.end()){
             it->second = stoul(value);
             count++;           
         }
         
        }
        
      }
      file.close();
      mem_total = mem_info_map.at("MemTotal:");
      mem_free = mem_info_map.at("MemFree:");
      if (mem_total != 0)
      {
      return 1 - mem_free/(float)mem_total;
      }
      
      //rest of the values i read may be I will use in feaute
  }

  ///for case if we cannt open file
  return 0.0; 
  }

// Read and return the system uptime
/// 
long int LinuxParser::UpTime() { 
  std::ifstream file(kProcDirectory + kUptimeFilename);
  if(file.is_open()){
    string first_word;
    file >> first_word;
  ///  std::cout << "first " << first_word << std::endl;
    string cutted_string = first_word.substr(0, first_word.find_first_of('.'));
   /// std::cout << "cutted " << cutted_string << std::endl;
   long int res = stoi(cutted_string);
  //  std::cout << "res " << res << std::endl;
  file.close();
    return res;
  }


  return 0; 
  }

//I really didnt understand where I found this jiffies all of them
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu_infos_v(10);
std::ifstream file(kProcDirectory + kStatFilename);
if(file.is_open()){
  int iIndex = 0;
  bool first = true;

 // std::cout << "before ";
  while ((iIndex < 10) && (file>>cpu_infos_v[iIndex]))
  {
    if (first)
    {
      first = false;
      if (cpu_infos_v[iIndex]=="cpu")
      {
        continue;
      }
      
    }
    
    iIndex++;
  }
  file.close();
  //for (string s : cpu_infos_v)
 // {
  //  std::cout << "i "<< s << " ";
 // }
  return cpu_infos_v;

}
  return {}; 
  }

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream file(kProcDirectory + kStatFilename);
if(file.is_open()){
  string line, name, value;
  while (std::getline(file, line))
  {
   if (line.substr(0, 9)=="processes")
   {
 ////    std::cout << "we found {" << line.substr(10) << "}";
    file.close();
     return stoi(line.substr(10));
   }
  }
  file.close();
  
}
  return 0; 
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
    std::ifstream file(kProcDirectory + kStatFilename);
if(file.is_open()){
  string line, name, value;
  while (std::getline(file, line))
  {
   if (line.substr(0, 13)=="procs_running")
   {
    file.close();
     return stoi(line.substr(14));
   }
  }
  file.close();
  
}
  return 0;
   }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  return string(); 
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }