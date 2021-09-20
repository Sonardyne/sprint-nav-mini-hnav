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
#ifndef HANV_DECODER__HNAVMESSAGE_H_
#define HANV_DECODER__HNAVMESSAGE_H_

#include <stdint.h>
#include <iostream>

class HnavMessage {
 public:
  uint8_t GetVersion() const {
    return version_;
  }
  void SetVersion(uint8_t version) {
    HnavMessage::version_ = version;
  }
  double GetTimeUtcSec() const {
    return time_utc_sec_;
  }

  void SetTimeUtcSec(double time_utc_sec) {
    time_utc_sec_ = time_utc_sec;
  }
  double GetLatitudeDeg() const {
    return latitude_deg_;
  }
  void SetLatitudeDeg(double latitude_deg) {
    latitude_deg_ = latitude_deg;
  }
  double GetLongitudeDeg() const {
    return longitude_deg_;
  }
  void SetLongitudeDeg(double longitude_deg) {
    longitude_deg_ = longitude_deg;
  }
  double GetDepthMetres() const {
    return depth_metres_;
  }
  void SetDepthMetres(double depth_metres) {
    depth_metres_ = depth_metres;
  }
  double GetAltitudeMetres() const {
    return altitude_metres_;
  }
  void SetAltitudeMetres(double altitude_metres) {
    altitude_metres_ = altitude_metres;
  }
  double GetRollDeg() const {
    return roll_deg_;
  }
  void SetRollDeg(double roll_deg) {
    roll_deg_ = roll_deg;
  }
  double GetPitchDeg() const {
    return pitch_deg_;
  }
  void SetPitchDeg(double pitch_deg) {
    pitch_deg_ = pitch_deg;
  }
  double GetHeadingDeg() const {
    return heading_deg_;
  }
  void SetHeadingDeg(double heading_deg) {
    heading_deg_ = heading_deg;
  }
  double GetVelocityFwdMetresPerSecond() const {
    return velocity_fwd_metres_per_second_;
  }
  void SetVelocityFwdMetresPerSecond(double velocity_fwd_metres_per_second) {
    velocity_fwd_metres_per_second_ = velocity_fwd_metres_per_second;
  }
  double GetVelocityStbdMetresPerSecond() const {
    return velocity_stbd_metres_per_second_;
  }
  void SetVelocityStbdMetresPerSecond(double velocity_stbd_metres_per_second) {
    velocity_stbd_metres_per_second_ = velocity_stbd_metres_per_second;
  }
  double GetVelocityDownMetresPerSecond() const {
    return velocity_down_metres_per_second_;
  }
  void SetVelocityDownMetresPerSecond(double velocity_down_metres_per_second) {
    velocity_down_metres_per_second_ = velocity_down_metres_per_second;
  }
  double GetAngularRateFwdDegPerSecond() const {
    return angular_rate_fwd_deg_per_second_;
  }
  void SetAngularRateFwdDegPerSecond(double angular_rate_fwd_deg_per_second) {
    angular_rate_fwd_deg_per_second_ = angular_rate_fwd_deg_per_second;
  }
  double GetAngularRateStbdDegPerSecond() const {
    return angular_rate_stbd_deg_per_second_;
  }
  void SetAngularRateStbdDegPerSecond(double angular_rate_stbd_deg_per_second) {
    angular_rate_stbd_deg_per_second_ = angular_rate_stbd_deg_per_second;
  }
  double GetAngularRateDownDegPerSecond() const {
    return angular_rate_down_deg_per_second_;
  }
  void SetAngularRateDownDegPerSecond(double angular_rate_down_deg_per_second) {
    angular_rate_down_deg_per_second_ = angular_rate_down_deg_per_second;
  }
  double GetSoundVelocityMetresPerSecond() const {
    return sound_velocity_metres_per_second_;
  }
  void SetSoundVelocityMetresPerSecond(double sound_velocity_metres_per_second) {
    sound_velocity_metres_per_second_ = sound_velocity_metres_per_second;
  }
  double GetTemperatureCelsius() const {
    return temperature_celsius_;
  }
  void SetTemperatureCelsius(double temperature_celsius) {
    temperature_celsius_ = temperature_celsius;
  }
  double GetPositionQualityCep50() const {
    return position_quality_cep_50_;
  }
  void SetPositionQualityCep50(double position_quality_cep_50) {
    position_quality_cep_50_ = position_quality_cep_50;
  }
  double GetHeadingQualityDegrees() const {
    return heading_quality_degrees_;
  }
  void SetHeadingQualityDegrees(double heading_quality_degrees) {
    heading_quality_degrees_ = heading_quality_degrees;
  }
  double GetVelocityQualityMilliMetresPerSecond() const {
    return velocity_quality_milli_metres_per_second_;
  }
  void SetVelocityQualityMilliMetresPerSecond(double velocity_quality_milli_metres_per_second) {
    velocity_quality_milli_metres_per_second_ = velocity_quality_milli_metres_per_second;
  }
  bool IsSystemError() const {
    return system_error_;
  }
  void SetSystemError(bool system_error) {
    system_error_ = system_error;
  }
  bool IsHybridMode() const {
    return hybrid_mode_;
  }
  void SetHybridMode(bool hybrid_mode) {
    hybrid_mode_ = hybrid_mode;
  }
  bool IsHeadingValid() const {
    return heading_valid_;
  }
  void SetHeadingValid(bool heading_valid) {
    heading_valid_ = heading_valid;
  }
  bool IsAltitudeValid() const {
    return altitude_valid_;
  }
  void SetAltitudeValid(bool altitude_valid) {
    altitude_valid_ = altitude_valid;
  }
  bool IsVelocityValid() const {
    return velocity_valid_;
  }
  void SetVelocityValid(bool velocity_valid) {
    velocity_valid_ = velocity_valid;
  }
  bool IsDepthValid() const {
    return depth_valid_;
  }
  void SetDepthValid(bool depth_valid) {
    depth_valid_ = depth_valid;
  }
  bool IsPositionValid() const {
    return position_valid_;
  }
  void SetPositionValid(bool position_valid) {
    position_valid_ = position_valid;
  }
  bool IsSoundVelocityValid() const {
    return sound_velocity_valid_;
  }
  void SetSoundVelocityValid(bool sound_velocity_valid) {
    sound_velocity_valid_ = sound_velocity_valid;
  }
  bool IsTemperatureValid() const {
    return temperature_valid_;
  }
  void SetTemperatureValid(bool temperature_valid) {
    temperature_valid_ = temperature_valid;
  }

  void PrintData() {
    std::cout << "\t*****\tTime\t\t\t*****" << std::endl;
    std::cout << "\t\tUTC Time: " << GetTimeUtcSec() << std::endl;
    std::cout << "\t*****\t2-D Position\t\t*****" << std::endl;
    if (IsPositionValid()) {
      std::cout << "\t\tLatitude (degrees): " << GetLatitudeDeg() << std::endl;
      std::cout << "\t\tLongitude (degrees): " << GetLongitudeDeg() << std::endl;
      std::cout << "\t\tPosition Quality (CEP50): " << GetPositionQualityCep50() << std::endl;
    } else {
      std::cout << "\t\tPosition invalid" << std::endl;
    }
    std::cout << "\t*****\tDepth\t\t\t*****" << std::endl;
    if (IsDepthValid()) {
      std::cout << "\t\tDepth (Metres): " << GetDepthMetres() << std::endl;
    } else {
      std::cout << "\t\tDepth Invalid" << std::endl;
    }

    std::cout << "\t*****\tAltitude\t\t*****" << std::endl;
    if (IsAltitudeValid()) {
      std::cout << "\t\tAltitude (Metres): " << GetAltitudeMetres() << std::endl;
    } else {
      std::cout << "\t\tAltitude Invalid" << std::endl;
    }

    std::cout << "\t*****\tOrientation\t\t*****" << std::endl;
    if (IsHeadingValid()) {
      std::cout << "\t\tRoll (degrees): " << GetRollDeg() << std::endl;
      std::cout << "\t\tPitch (degrees): " << GetPitchDeg() << std::endl;
      std::cout << "\t\tHeading (degrees): " << GetHeadingDeg() << std::endl;
      std::cout << "\t\tHeading Quality (degrees): " << GetHeadingQualityDegrees() << std::endl;
    } else {
      std::cout << "\t\tOrientation is invalid" << std::endl;
    }

    std::cout << "\t*****\tVelocities\t\t******" << std::endl;
    if (IsVelocityValid()) {
      std::cout << "\t\tVelocity, Vehicle Forward (m/s): " << GetVelocityFwdMetresPerSecond() << std::endl;
      std::cout << "\t\tVelocity, Vehicle Starboard (m/s): " << GetVelocityStbdMetresPerSecond() << std::endl;
      std::cout << "\t\tVelocity, Vehicle Down (m/s): " << GetVelocityDownMetresPerSecond() << std::endl;
      std::cout << "\t\tVelocity Quality (mm/s): " << GetVelocityQualityMilliMetresPerSecond() << std::endl;
    } else {
      std::cout << "\t\tVelocities Invalid" << std::endl;
    }

    std::cout << "\t*****\tAngular Rates\t\t*****" << std::endl;
    std::cout << "\t\tAngular Rate, Vehicle Forward (deg/s): " << GetAngularRateFwdDegPerSecond() << std::endl;
    std::cout << "\t\tAngular Rate, Vehicle Starboard (deg/s): " << GetAngularRateStbdDegPerSecond() << std::endl;
    std::cout << "\t\tAngular Rate, Vehicle Down (deg/s): " << GetAngularRateDownDegPerSecond() << std::endl;

    std::cout << "\t*****\tSound Velocity\t\t*****" << std::endl;
    if (IsSoundVelocityValid())
    {
    std::cout << "\t\tSound Velocity (m/s): " << GetSoundVelocityMetresPerSecond() << std::endl;}
    else
    {
      std::cout << "\t\tSound velocity Invalid" << std::endl;
    }

    std::cout << "\t*****\tWater Temperature\t*****" << std::endl;
    if (IsTemperatureValid()) {
      std::cout << "\t\tTemperature (degrees Celsius): " << GetTemperatureCelsius() << std::endl;
    } else {
      std::cout << "\t\tTemperature Invalid" << std::endl;
    }

    std::cout << "\t*****\tStatus\t\t\t*****" << std::endl;
    if (IsSystemError()) {
      std::cout << "\t\tSystem Error Present" << std::endl;
    }

    if (IsHybridMode()) {
      std::cout << "\t\tIn Hybrid Mode" << std::endl;
    } else {
      std::cout << "\t\tIn Sensor Mode" << std::endl;
    }
  }

 private:
  uint8_t version_{0};
  double time_utc_sec_{0.0};
  double latitude_deg_{0.0};
  double longitude_deg_{0.0};
  double depth_metres_{0.0};
  double altitude_metres_{0.0};
  double roll_deg_{0.0};
  double pitch_deg_{0.0};
  double heading_deg_{0.0};
  double velocity_fwd_metres_per_second_{0.0};
  double velocity_stbd_metres_per_second_{0.0};
  double velocity_down_metres_per_second_{0.0};
  double angular_rate_fwd_deg_per_second_{0.0};
  double angular_rate_stbd_deg_per_second_{0.0};
  double angular_rate_down_deg_per_second_{0.0};
  double sound_velocity_metres_per_second_{0.0};
  double temperature_celsius_{0.0};
  double position_quality_cep_50_{0.0};
  double heading_quality_degrees_{0.0};
  double velocity_quality_milli_metres_per_second_{0.0};
  bool system_error_ = false;
  bool hybrid_mode_ = false;
  bool heading_valid_ = false;
  bool altitude_valid_ = false;
  bool velocity_valid_ = false;
  bool depth_valid_ = false;
  bool position_valid_ = false;
  bool sound_velocity_valid_ = false;
  bool temperature_valid_ = false;
};

#endif //HANV_DECODER__HNAVMESSAGE_H_
