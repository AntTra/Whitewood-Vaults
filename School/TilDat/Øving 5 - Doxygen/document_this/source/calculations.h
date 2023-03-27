/** 
 * @file 
 * @brief Woah. This thing defines some calculations of the parameters of P I D using Classic-Ziegler-Nichols","Pessens Integral Rule"
 */
#ifndef CALCULATIONS_H
#define CALCUATIONS_H
#include "system.h"

/**
 * @brief Hello. This function calculates the proportional parameters of the current system
 * @param[in] System
 * @param[out] current_system
 */
double calculate_P_parameter(System * current_system);

/**
 * @brief This function calculates the integer parameters of the current system
 * @param[in] System 
 * @param[out] current_system
 */
double calculate_I_parameter(System * current_system);

/**
 * @brief This function calculates the derivative parameters of the current system
 * @param[in] System 
 * @param[out] current_system
 */
double calculate_D_parameter(System * current_system);

#endif
