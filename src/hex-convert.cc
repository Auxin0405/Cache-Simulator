#include "hex-convert.h"

#include <string>
#include <sstream>

std::string
HexConvert::Hex2String (uint32_t hex)
{
  // Just use std::stringstream to complete tranform
  std::string res;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> res;

  // to clarify the string res is Hex result, add "H" at the end
  return res + "H";
}

uint32_t
HexConvert::String2Hex (std::string& str)
{
  // Same as Hex2String
  uint32_t res;
  std::stringstream ss;
  ss << std::hex << str;
  ss >> res;
  return res;
}