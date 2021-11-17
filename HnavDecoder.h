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

#ifndef HANV_DECODER__HNAVDECODER_H_
#define HANV_DECODER__HNAVDECODER_H_

#include <stdint.h>
#include <vector>
#include <deque>
#include <cmath>
#include "HnavMessage.h"



class HnavDecoder {
 public:
  HnavDecoder(){};
  ~HnavDecoder(){};
  void Init();
  void AddBytes(const std::vector<uint8_t> &data);
  bool GetMessage(HnavMessage &message);

 private:
  // maximum number of elements allowed in the queue
  const uint16_t kMaxQueueSize{1024};
  // Fixed byte values for HNAV and protocol
  const uint8_t kStartByte{0xAA};
  const uint8_t kSecondByte{0xBF};
  const uint8_t kProtocolVersion{0};
  const uint16_t kMessageId{0x0};
  const uint16_t kMessageDataSize{55};
  const uint16_t kHeaderAndCrcSize{12};
  const uint32_t kExpectedDataAndProtocolSize{kMessageDataSize + kHeaderAndCrcSize};
  const double kHnavUtcScale{pow(10,-6)};
  const double kHnavLatScale{90.0* pow(2,-31)};
  const double kHnavLonScale{180.0* pow(2,-31)};
  const double kHnavDepthScale{pow(10.0,-3)};
  const double kHnavAltScale{pow(10.0,-2)};
  const double kHnavOrientationScale{0.0055};
  const double kHnavVelocityScale{pow(10,-3)};
  const double kHnavAngVelocityScale{0.011};
  const double kHnavSoundVelocityScale{0.03};
  const double kHnavTemperatureScale{pow(10,-2)};
  const double kHnavPositionQualityScale{1.0};
  const double kHnaveHeadingQualityScale{0.005};
  const double kHnavVelocityQualityScale{pow(10,-3)};
  const uint16_t kHnavSystemErrorMask{0x0001};
  const uint16_t kHnavModeMask{0x0002};
  const uint16_t kHnavHeadingValidMask{0x0004};
  const uint16_t kHnavAltitudeValidMask{0x0008};
  const uint16_t kHnavVelocityValidMask{0x0010};
  const uint16_t kHnavDepthValidMask{0x0020};
  const uint16_t kHnavSoundVelocityValidMask{0x0040};
  const uint16_t kHnavTemperatureValidMask{0x0080};
  const uint16_t kHnavPosisionValidMask{0x0200};



  // queue of data awaiting processing
  std::deque<uint8_t> data_;

  // assumes that the data in the queue starting at byte 0 is a candidate HNAV.
  bool CheckCrc();

  // decode message into payload, assumes that the data in the queue starting at byte0
  // is a HNAV message with header still inplace.
  void DecodeMessage(HnavMessage &message);
};

#endif //HANV_DECODER__HNAVDECODER_H_
