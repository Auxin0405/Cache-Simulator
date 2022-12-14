#include "src/hex-convert.h"
#include "src/core.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

uint32_t core_num = 2;

// Do two things:
// 1. Start Read the Trace File
// 2. Log Out
int main ()
{
  Core core(core_num);

  // First, Get the input.
  // Use to get the Trace Input;
  std::ifstream input[core_num];
  // Read Trace File
  for (uint32_t i = 0; i < core_num; i++)
    input[i].open ("./trace/trace" + std::to_string(i));

  // Set Outstream
  std::ofstream out ("./trace/out");

  out << "Step: \t\tAddress\t\t\tMainMemory\t\t";
  for (uint32_t i  = 0; i < core_num; i++) {
    out << "Core: " << i << "Cache\t\t";
  }
  out << std::endl;

  // Read and Run
  // Run something core by core.
  while (true) {
    int cnt = 0;
    for (uint32_t i = 0; i < core_num; i++) {
      std::string line;
      // Help ensure the line num
      uint32_t j = 0;
      // Get the input line.
      if (std::getline (input[i], line)) {
        uint32_t opt, addr;
        std::stringstream ss(line);
        if (ss >> opt >> std::hex >> addr) {
          core.Run(i, opt, Address(addr));
          core.PrintState (out, opt, addr);
        }
      } else {
        cnt ++;
      }
    }
    if (cnt == core_num)
      break;
  }

  out.close ();
  for (uint32_t i = 0; i < core_num; i++)
    input[i].close ();
  return 0;
}