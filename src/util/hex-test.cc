#include "hex-convert.h"

#include "iostream"
#include "string"

int main ()
{
  std::string hex = "A221C";
  uint32_t x = 12312321;
  std::cout << "Hex convert to string: " << HexConvert::Hex2String (x) << std::endl;
  std::cout << "String convert to hex: " << HexConvert::String2Hex (hex) << std::endl;
}