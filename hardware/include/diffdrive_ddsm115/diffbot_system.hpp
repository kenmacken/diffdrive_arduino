// Copyright 2021 ros2_control Development Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DIFFDRIVE_DDSM115__DIFFBOT_SYSTEM_HPP_
#define DIFFDRIVE_DDSM115__DIFFBOT_SYSTEM_HPP_

#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/clock.hpp"
#include "rclcpp/duration.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/time.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "rclcpp_lifecycle/state.hpp"
#include "diffdrive_ddsm115/visibility_control.h"

#include "diffdrive_ddsm115/wheel.hpp"
#include "diffdrive_ddsm115/ddsm115_comms.hpp"

#include "diffdrive_ddsm115/imu.hpp"
#include "diffdrive_ddsm115/mcu_comms.hpp"


namespace diffdrive_ddsm115
{
class DiffDriveDDSM115Hardware : public hardware_interface::SystemInterface
{

struct Config
{
  std::string left_wheel_name = "";
  std::string right_wheel_name = "";
  std::string device = "";
  int baud_rate = 115200;
  int timeout_ms = 0;
  int left_wheel_id = 0;
  int right_wheel_id = 2;
  std::string imu_device = "";
  int imu_baud_rate = 57600;
  int imu_id = 1;
};


public:
  RCLCPP_SHARED_PTR_DEFINITIONS(DiffDriveDDSM115Hardware);

  DIFFDRIVE_DDSM115_PUBLIC
  hardware_interface::CallbackReturn on_init(
    const hardware_interface::HardwareInfo & info) override;

  DIFFDRIVE_DDSM115_PUBLIC
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  DIFFDRIVE_DDSM115_PUBLIC
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  DIFFDRIVE_DDSM115_PUBLIC
  hardware_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & previous_state) override;

  DIFFDRIVE_DDSM115_PUBLIC
  hardware_interface::CallbackReturn on_cleanup(
    const rclcpp_lifecycle::State & previous_state) override;


  DIFFDRIVE_DDSM115_PUBLIC
  hardware_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  DIFFDRIVE_DDSM115_PUBLIC
  hardware_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  DIFFDRIVE_DDSM115_PUBLIC
  hardware_interface::return_type read(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  DIFFDRIVE_DDSM115_PUBLIC
  hardware_interface::return_type write(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:
  DDSM115Comms commsDDSM_;
  Config cfg_;
  Wheel wheel_l_;
  Wheel wheel_r_;
  mcuComms mcuComms_;
  IMU imu_;
};

}  // namespace diffdrive_ddsm115

#endif  // DIFFDRIVE_DDSM115__DIFFBOT_SYSTEM_HPP_
