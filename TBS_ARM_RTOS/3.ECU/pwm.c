#include <stdint.h>
#include <lpc11xx.h>
#include <common.h>
#include <clocks.h>
#include <ct32b1.h>
#include <gpio.h>
#include <pwm.h>

void Set_PWM_Duty(uint8_t duty) {
	uint32_t mat = 0;
	mat = PWM_CYCLE_COUNT - (10 * duty);
	Set_CT32B1_MAT0_Count(mat);
}
