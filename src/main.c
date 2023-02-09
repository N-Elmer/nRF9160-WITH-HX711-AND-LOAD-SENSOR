/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/types.h>

#include <sensor/hx711/hx711.h>
#include <stddef.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

const struct device *hx711_dev;

// void set_rate(enum hx711_rate rate)
// {
// 	static struct sensor_value rate_val;

// 	rate_val.val1 = rate;
// 	sensor_attr_set(hx711_dev,
// 			HX711_SENSOR_CHAN_WEIGHT,
// 			SENSOR_ATTR_SAMPLING_FREQUENCY,
// 			&rate_val);
// }

void measure(void)
{
	static struct sensor_value weight;
	int ret;

	ret = sensor_sample_fetch(hx711_dev);
	if (ret != 0) {
		LOG_ERR("Cannot take measurement: %d", ret);
	} else {
		sensor_channel_get(hx711_dev, HX711_SENSOR_CHAN_WEIGHT, &weight);
		LOG_INF("Weight: %d.%06d grams", weight.val1, weight.val2);
	}
}

void main(void) {
	int calibration_weight = 1000; // grams
	hx711_dev = DEVICE_DT_GET_ANY(avia_hx711);
	__ASSERT(hx711_dev == NULL, "Failed to get device binding");

	LOG_INF("Device is %p, name is %s", hx711_dev, hx711_dev->name);
	LOG_INF("Calculating offset...");
	avia_hx711_tare(hx711_dev, 5);

	LOG_INF("Waiting for known weight of %d grams...", calibration_weight);

	for (int i = 5; i >= 0; i--) {
		LOG_INF(" %d..", i);
		k_msleep(1000);
	}

	LOG_INF("Calculating slope...");
	avia_hx711_calibrate(hx711_dev, calibration_weight, 5);

	while (true) {
		// k_msleep(1000);
		// LOG_INF("== Test measure ==");
		// LOG_INF("= Setting sampling rate to 10Hz.");
		// set_rate(HX711_RATE_10HZ);
		measure();

		// k_msleep(1000);
		// LOG_INF("= Setting sampling rate to 80Hz.");
		// set_rate(HX711_RATE_80HZ);
		// measure();
		k_msleep(1000);
	}
}