///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2012, hiDOF INC.
// Copyright (C) 2013, PAL Robotics S.L.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of hiDOF, Inc. nor the names of its
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

/// \author Wim Meeussen

#pragma once


#include <hardware_interface/internal/hardware_resource_manager.h>
#include <string>

namespace hardware_interface
{

/**
 * \brief A handle used to read the state of a single actuator.
 * Currently, position, velocity and effort fields are required
 * while absolute position and torque sensors are optional.
 */
class ActuatorStateHandle
{
public:
  ActuatorStateHandle() : name_(), pos_(nullptr), vel_(nullptr), eff_(nullptr), absolute_pos_(nullptr), torque_sensor_(nullptr) {}

  /**
   * \param name The name of the actuator
   * \param pos A pointer to the storage for this actuator's position
   * \param vel A pointer to the storage for this actuator's velocity
   * \param eff A pointer to the storage for this actuator's effort (force or torque)
   */
  ActuatorStateHandle(const std::string& name, const double* pos, const double* vel, const double* eff)
    : name_(name), pos_(pos), vel_(vel), eff_(eff), absolute_pos_(nullptr), torque_sensor_(nullptr)
  {
    if (!pos)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Position data pointer is null.");
    }
    if (!vel)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Velocity data pointer is null.");
    }
    if (!eff)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Effort data pointer is null.");
    }
  }

  /**
   * \param name The name of the actuator
   * \param pos A pointer to the storage for this actuator's position
   * \param vel A pointer to the storage for this actuator's velocity
   * \param eff A pointer to the storage for this actuator's effort (force or torque)
   * \param absolute_pos A pointer to the storage for this actuator's absolute position encoder
   * \param torque_sensor A pointer to the storage for this actuator's torque sensor
   */
  ActuatorStateHandle(const std::string& name, const double* pos, const double* vel, const double* eff,
                      const double* absolute_pos, const double* torque_sensor)
    : name_(name), pos_(pos), vel_(vel), eff_(eff), absolute_pos_(absolute_pos), torque_sensor_(torque_sensor)
  {
    if (!pos)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Position data pointer is null.");
    }
    if (!vel)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Velocity data pointer is null.");
    }
    if (!eff)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Effort data pointer is null.");
    }

    if (!absolute_pos)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Absolute data pointer is null.");
    }
    if (!torque_sensor)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Torque sensor data pointer is null.");
    }
  }

  /**
   * \param name The name of the actuator
   * \param pos A pointer to the storage for this actuator's position
   * \param vel A pointer to the storage for this actuator's velocity
   * \param eff A pointer to the storage for this actuator's effort (force or torque)
   * \param absolute_pos A pointer to the storage for this actuator's absolute position encoder
   */
  ActuatorStateHandle(const std::string& name, const double* pos, const double* vel, const double* eff,
                      const double* absolute_pos)
    : name_(name), pos_(pos), vel_(vel), eff_(eff), absolute_pos_(absolute_pos), torque_sensor_(nullptr)
  {
    if (!pos)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Position data pointer is null.");
    }
    if (!vel)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Velocity data pointer is null.");
    }
    if (!eff)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Effort data pointer is null.");
    }
    if (!absolute_pos)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Absolute data pointer is null.");
    }
  }

  /**
   * \param name The name of the actuator
   * \param pos A pointer to the storage for this actuator's position
   * \param vel A pointer to the storage for this actuator's velocity
   * \param eff A pointer to the storage for this actuator's effort (force or torque)
   * \param torque_sensor A pointer to the storage for this actuator's torque sensor
   * \param bool Dummy parameter to differentiate from absolute encoder constructor
   */
  ActuatorStateHandle(const std::string& name, const double* pos, const double* vel, const double* eff,
                      const double* torque_sensor, bool)
    : name_(name), pos_(pos), vel_(vel), eff_(eff), absolute_pos_(nullptr), torque_sensor_(torque_sensor)
  {
    if (!pos)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Position data pointer is null.");
    }
    if (!vel)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Velocity data pointer is null.");
    }
    if (!eff)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Effort data pointer is null.");
    }
    if (!torque_sensor)
    {
      throw HardwareInterfaceException("Cannot create handle '" + name + "'. Torque sensor data pointer is null.");
    }
  }

  std::string getName() const {return name_;}
  double getPosition()  const {assert(pos_); return *pos_;}
  double getVelocity()  const {assert(vel_); return *vel_;}
  double getEffort()    const {assert(eff_); return *eff_;}

  double getAbsolutePosition() const
  {
    if(!hasAbsolutePosition())
    {
      throw std::runtime_error("Actuator does not support absolute encoders");
    }
    return *absolute_pos_;
  }

  double getTorqueSensor() const
  {
    if(!hasTorqueSensor())
    {
      throw std::runtime_error("Actuator does not support torque sensors");
    }
    return *torque_sensor_;
  }

  const double* getPositionPtr() const {return pos_;}
  const double* getVelocityPtr() const {return vel_;}
  const double* getEffortPtr()   const {return eff_;}

  const double* getAbsolutePositionPtr() const
  {
    if(!hasAbsolutePosition())
    {
      throw std::runtime_error("Actuator does not support absolute encoders");
    }
    return absolute_pos_;
  }

  const double* getTorqueSensorPtr() const
  {
    if(!hasTorqueSensor())
    {
      throw std::runtime_error("Actuator does not support torque sensors");
    }
    return torque_sensor_;
  }

  bool hasAbsolutePosition()  const {return absolute_pos_;}
  bool hasTorqueSensor()      const {return torque_sensor_;}

private:
  std::string name_;
  const double* pos_;
  const double* vel_;
  const double* eff_;
  const double* absolute_pos_;
  const double* torque_sensor_;
};

/** \brief Hardware interface to support reading the state of an array of actuators
 *
 * This \ref HardwareInterface supports reading the state of an array of named
 * actuators, each of which has some position, velocity, and effort (force or
 * torque).
 *
 */
class ActuatorStateInterface : public HardwareResourceManager<ActuatorStateHandle> {};

}
