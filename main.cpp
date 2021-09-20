//Copyright 2021 Sonardyne International Limited
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
//documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
//rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
//permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
//Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
//OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <iostream>
#include <vector>
#include <stdint.h>

#include "HnavDecoder.h"

int main() {

  // example received data
  std::vector<uint8_t> hnav_message_bytes {0xaa, 0xbf, 0x00, 0x00, 0x00, 0x37, 0x00, 0x86,
                                           0xde, 0xad, 0x00, 0x9c, 0x0e, 0x78, 0x03, 0x69,
                                           0xcc, 0x05, 0x00, 0x86, 0xea, 0x00, 0x49, 0xfc,
                                           0xdd, 0x67, 0xff, 0x79, 0xff, 0xff, 0xff, 0x00,
                                           0x00, 0xee, 0xff, 0xac, 0xff, 0xd3, 0x33, 0xfa,
                                           0xff, 0xfa, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x3a, 0xc6, 0xf1, 0x07, 0x49,
                                           0x63, 0xff, 0x3f, 0xb7, 0x01, 0x6b, 0x00, 0x8a,
                                           0x00, 0x93, 0xd0};
  HnavDecoder hnav_decoder;
  HnavMessage message;

  hnav_decoder.AddBytes(hnav_message_bytes);

  if (hnav_decoder.GetMessage(message)) {
    std::cout << "Valid HNav message detected in data provided to decoder. Decoded as: " << std::endl;
    message.PrintData();
  } else {
    std::cout << "No Valid HNav message detected in data provided to decoder" << std::endl;
  }
  return 0;
}
