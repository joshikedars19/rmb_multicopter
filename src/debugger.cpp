#include "debugger.h"
#include <Arduino.h>
#include "imu.h"
#include "pids.h"
#include "flight_controller.h"
#include "motors.h"

int32_t debug_timer = millis();
int32_t loop_timer = micros();
int32_t loop_duration;

void text_debug() {
  Serial.print("pid_x_kp: "); Serial.print(pid(PID_RATE_X)->kp);
  Serial.print("\t pid_x_ki: "); Serial.print(pid(PID_RATE_X)->ki);
  Serial.println();

  Serial.print("gyro_x: "); Serial.print(imu_rates().x);
  Serial.print("\t pid_x_out: "); Serial.print(pid(PID_RATE_X)->output);
  Serial.print("\t pid_x_p: "); Serial.print(pid(PID_RATE_X)->p_term);
  Serial.print("\t pid_x_i: "); Serial.print(pid(PID_RATE_X)->i_term);
  Serial.println();

  Serial.print("gyro_y: "); Serial.print(imu_rates().y);
  Serial.print("\t pid_y_out: "); Serial.print(pid(PID_RATE_Y)->output);
  Serial.print("\t pid_y_p: "); Serial.print(pid(PID_RATE_Y)->p_term);
  Serial.print("\t pid_y_i: "); Serial.print(pid(PID_RATE_Y)->i_term);
  Serial.println();

  Serial.print("gyro_z: "); Serial.print(imu_rates().z);
  Serial.println();

  Serial.print("throttle: "); Serial.print(fc_throttle());
  Serial.print("\tm1: "); Serial.print(motor_level(M1));
  Serial.print("\tm2: "); Serial.print(motor_level(M2));
  Serial.print("\tm3: "); Serial.print(motor_level(M3));
  Serial.print("\tm4: "); Serial.print(motor_level(M4));
  if (fc_armed()) {
    Serial.print("\t ARMED");
  } else {
    Serial.print("\t UNARMED");
  }

  Serial.println();

  //Serial.print("gyro_x_ang: "); Serial.print(imu_gyro_angles().x);
  //Serial.print("\t gyro_y_ang: "); Serial.print(imu_gyro_angles().y);
  //Serial.println();

  //Serial.print("accel_x_raw: "); Serial.print(imu_accel_raws().x);
  //Serial.print("\t accel_y_raw: "); Serial.print(imu_accel_raws().y);
  //Serial.print("\t accel_z_raw: "); Serial.print(imu_accel_raws().z);
  //Serial.println();

  //Serial.print("accel_x_angle: "); Serial.print(imu_accel_angles().x);
  //Serial.print("\t accel_y_angle: "); Serial.print(imu_accel_angles().y);
  //Serial.println();

  //Serial.print("x_angle: "); Serial.print(imu_angles().x);
  //Serial.print("\t y_angle: "); Serial.print(imu_angles().y);
  //Serial.println();

  Serial.print("loop time: "); Serial.print(loop_duration);
  Serial.println();

  Serial.println();
}

void chart_debug() {
  //Serial.print(imu_gyro_angles().x);
  Serial.print(imu_rates().x);
  Serial.print(" ");
  //Serial.print(imu_accel_angles().x);
  Serial.print(imu_gyro_rates().x);
  Serial.print(" ");
  Serial.print(imu_angles().x);
  Serial.print(" ");
  Serial.print(1);
  Serial.print(" ");
  Serial.print(1);
  Serial.print(" ");
  Serial.print(1);
  Serial.print("\r");
}

void print_debug() {
  if (CHART_DEBUG) {
    chart_debug();
  } else {
    text_debug();
  }
}

void debugger_print() {
  loop_duration = micros() - loop_timer;

  if (DEBUG && millis() - debug_timer > DEBUG_RATE_MILLIS) {
    print_debug();
    debug_timer = millis();
  }

  loop_timer = micros();
}
