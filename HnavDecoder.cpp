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

#include "HnavDecoder.h"

// This function adds the provided bytes to the internal queue of data bytes
// if the list will grow beyond its limit then the oldest data will be removed.

void HnavDecoder::AddBytes(const std::vector<uint8_t> &data) {
  for (uint8_t i : data) {
    if (data_.size() == kMaxQueueSize) {
      data_.pop_front();
    }
    data_.push_back(i);
  }
}

// This function will return true if a valid message has been found in the internal queue
// this message will be returned via the provided HnavMessage reference

bool HnavDecoder::GetMessage(HnavMessage &message) {
  bool ret_value(false);

  // loop over elements in queue to see if we can find the start bytes, stop looping
  // if queue is empty or the number of bytes in queue is smaller than expected message size
  while ((!data_.empty()) && (data_.size() >= kExpectedDataAndProtocolSize)) {
    if (data_.front() == kStartByte) {
      if (data_.at(1) == kSecondByte) {
        // candidate message => check message ID field to see if this is an HNAV, uint16_t field so check
        // the next two bytes are 0, also check version, only support version 0 and we also expect data size
        // to be 55
        uint16_t message_id = data_.at(3) | (data_.at(4) << 8);
        uint16_t data_size = data_.at(5) | (data_.at(6) << 8);
        if ((data_.at(2) == kProtocolVersion) && (message_id == kMessageId) && (data_size == kMessageDataSize)) {
          // now check the CRC
          if (CheckCrc()) {
            // valid CRC, decode message data
            DecodeMessage(message);
            // remove all the used bytes
            for (uint16_t i = 0; i < kExpectedDataAndProtocolSize; i++) {
              data_.pop_front();
            }

            ret_value = true;
            break;

          } else {
            // not a valid message, so remove the two header bytes and carry on searching
            data_.pop_front();
            data_.pop_front();
          }
        } else {
          //not a HNAV message so remove the first two header bytes from the queue
          data_.pop_front();
          data_.pop_front();
        }

      } else {
        // we have not found a start sequence, only pop the first byte as the second byte might be the
        // start of a new header and will be checked on the next pass
        data_.pop_front();
      }
    } else {
      // not the start byte so pop from queue
      data_.pop_front();
    }
  }

  return ret_value;
}

uint32_t reflect(uint32_t crc, uint32_t bit_num) {
  // reflects the lower 'bit_num' bits of 'crc'
  unsigned long i, j = 1, crc_out = 0;

  for (i = (uint32_t) 1 << (bit_num - 1); i; i >>= 1) {
    if (crc & i)
      crc_out |= j;
    j <<= 1;
  }
  return (crc_out);
}

// assumes that the data in the queue starting at byte 0 is a candidate HNAV.
bool HnavDecoder::CheckCrc() {

  uint32_t crc(0xffff);
  uint16_t i(0);
  uint32_t j(0);
  uint32_t current_byte(0);
  uint32_t bit(0);
  uint32_t data_crc(0);

  // data starts at byte 10
  for (i = 0; i < (kExpectedDataAndProtocolSize - 2); i++) {
    current_byte = data_.at(i);
    current_byte = reflect(current_byte, 8);

    for (j = 0x80; j; j >>= 1) {

      bit = crc & 0x8000;
      crc <<= 1;
      if (current_byte & j)
        bit ^= 0x8000;
      if (bit)
        crc ^= 0x1021;
    }
  }

  crc = reflect(crc, 16);
  crc ^= 0xffff;
  crc &= 0xffff;

  // calculate data CRC
  data_crc = data_.at(65) | (data_.at(66) << 8);

  return (data_crc == crc);
}

void HnavDecoder::DecodeMessage(HnavMessage &message) {
  // the assumption here is that the first element in the queue is the first byte of the header (0xAA)
  // and we can therefore hard-code the byte offsets in the queue for the data we require.
  message.SetVersion(data_.at(10));
  uint64_t temp_time =
      data_.at(11) | (static_cast<uint64_t>(data_.at(12)) << 8) | (static_cast<uint64_t>(data_.at(13)) << 16) | (static_cast<uint64_t>(data_.at(14))<< 24) | (static_cast<uint64_t>(data_.at(15)) << 32)
      | (static_cast<uint64_t>(data_.at(16)) << 40) | (static_cast<uint64_t>(data_.at(17)) << 48) | (static_cast<uint64_t>(data_.at(18)) << 56);
  message.SetTimeUtcSec(static_cast<double>(temp_time) * kHnavUtcScale);

  uint32_t temp_lat = data_.at(19) | (static_cast<uint32_t>(data_.at(20)) << 8)| (static_cast<uint32_t>(data_.at(21)) << 16)| (static_cast<uint32_t>(data_.at(22)) << 24);
  message.SetLatitudeDeg(static_cast<double>(static_cast<int32_t>(temp_lat)) * kHnavLatScale);

  uint32_t temp_lon = data_.at(23) | (static_cast<uint32_t>(data_.at(24)) << 8)| (static_cast<uint32_t>(data_.at(25)) << 16)| (static_cast<uint32_t>(data_.at(26)) << 24);
  message.SetLongitudeDeg(static_cast<double>(static_cast<int32_t>(temp_lon)) * kHnavLonScale);

  uint32_t temp_depth = data_.at(27) | (static_cast<uint32_t>(data_.at(28)) << 8)| (static_cast<uint32_t>(data_.at(29)) << 16)| (static_cast<uint32_t>(data_.at(30)) << 24);
  message.SetDepthMetres(static_cast<double>(static_cast<int32_t>(temp_depth)) * kHnavDepthScale);

  uint16_t temp_alt = data_.at(31) | (static_cast<uint16_t>(data_.at(32))<< 8);
  message.SetAltitudeMetres(static_cast<double>(temp_alt) * kHnavAltScale);

  uint16_t temp_roll = data_.at(33) | (static_cast<uint16_t>(data_.at(34))<< 8);
  message.SetRollDeg(static_cast<double>(static_cast<int16_t >(temp_roll)) * kHnavOrientationScale);

  uint16_t temp_pitch = data_.at(35) | (static_cast<uint16_t>(data_.at(36))<< 8);
  message.SetPitchDeg(static_cast<double>(static_cast<int16_t >(temp_pitch)) * kHnavOrientationScale);

  uint16_t temp_heading = data_.at(37) | (static_cast<uint16_t>(data_.at(38))<< 8);
  message.SetHeadingDeg(static_cast<double>(static_cast<int16_t >(temp_heading)) * kHnavOrientationScale);

  uint16_t temp_vel_fwd = data_.at(39) | (static_cast<uint16_t>(data_.at(40))<< 8);
  message.SetVelocityFwdMetresPerSecond(static_cast<double>(static_cast<int16_t >(temp_vel_fwd)) * kHnavVelocityScale);

  uint16_t temp_vel_stbd = data_.at(41) | (static_cast<uint16_t>(data_.at(42))<< 8);
  message.SetVelocityStbdMetresPerSecond(static_cast<double>(static_cast<int16_t >(temp_vel_stbd)) * kHnavVelocityScale);

  uint16_t temp_vel_down = data_.at(43) | (static_cast<uint16_t>(data_.at(44))<< 8);
  message.SetVelocityDownMetresPerSecond(static_cast<double>(static_cast<int16_t >(temp_vel_down)) * kHnavVelocityScale);

  uint16_t temp_ang_fwd = data_.at(45) | (static_cast<uint16_t>(data_.at(46))<< 8);
  message.SetAngularRateFwdDegPerSecond(static_cast<double>(static_cast<int16_t >(temp_ang_fwd)) * kHnavAngVelocityScale);

  uint16_t temp_ang_stbd = data_.at(47) | (static_cast<uint16_t>(data_.at(48))<< 8);
  message.SetAngularRateStbdDegPerSecond(static_cast<double>(static_cast<int16_t >(temp_ang_stbd)) * kHnavAngVelocityScale);

  uint16_t temp_ang_down = data_.at(49) | (static_cast<uint16_t>(data_.at(50))<< 8);
  message.SetAngularRateDownDegPerSecond(static_cast<double>(static_cast<int16_t >(temp_ang_down)) * kHnavAngVelocityScale);

  uint16_t temp_sound_velocity = data_.at(51) | (static_cast<uint16_t>(data_.at(52))<< 8);
  message.SetSoundVelocityMetresPerSecond(static_cast<double>(temp_sound_velocity) * kHnavSoundVelocityScale);

  uint16_t temp_temperature = data_.at(53) | (static_cast<uint16_t>(data_.at(54))<< 8);
  message.SetTemperatureCelsius(static_cast<double>(static_cast<int16_t >(temp_temperature)) * kHnavTemperatureScale);

  // the following converts the four bytes as stored in the message in to the corresponding floating point representation.
  // care needs to be taken that the following matches the floating point representation on the target CPU.
  uint8_t byte_array[] = {data_.at(55),data_.at(56),data_.at(57),data_.at(58)};
  float position_quality_result;
  std::copy(reinterpret_cast<const char*>(&byte_array[0]),reinterpret_cast<const char*>(&byte_array[4]),
            reinterpret_cast<char*>(&position_quality_result));
  message.SetPositionQualityCep50(static_cast<double>(static_cast<float>(position_quality_result)) * kHnavPositionQualityScale);

  uint16_t temp_heading_quality = data_.at(59) | (static_cast<uint16_t>(data_.at(60))<< 8);
  message.SetHeadingQualityDegrees(static_cast<double>(static_cast<int16_t >(temp_heading_quality)) * kHnaveHeadingQualityScale);

  uint16_t temp_velocity_quality = data_.at(61) | (static_cast<uint16_t>(data_.at(62))<< 8);
  message.SetVelocityQualityMilliMetresPerSecond(static_cast<double>(static_cast<int16_t >(temp_velocity_quality)) * kHnavVelocityQualityScale);

  uint16_t temp_status = data_.at(63) | (static_cast<uint16_t>(data_.at(64))<< 8);

  message.SetSystemError((temp_status & kHnavSystemErrorMask) == kHnavSystemErrorMask);
  message.SetHybridMode((temp_status & kHnavModeMask) == kHnavModeMask);
  message.SetHeadingValid((temp_status & kHnavHeadingValidMask) != kHnavHeadingValidMask);
  message.SetAltitudeValid((temp_status & kHnavAltitudeValidMask) != kHnavAltitudeValidMask);
  message.SetVelocityValid((temp_status & kHnavVelocityValidMask) != kHnavVelocityValidMask);
  message.SetDepthValid((temp_status & kHnavDepthValidMask) != kHnavDepthValidMask);
  message.SetSoundVelocityValid((temp_status & kHnavSoundVelocityValidMask) != kHnavSoundVelocityValidMask);
  message.SetTemperatureValid((temp_status & kHnavTemperatureValidMask) != kHnavTemperatureValidMask);
  message.SetPositionValid((temp_status & kHnavPosisionValidMask) != kHnavPosisionValidMask );

}