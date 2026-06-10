/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Minimal PM implementation stubs for Zephyr.
 * These stubs are needed when pm_impl.c is not compiled (it requires FreeRTOS).
 */

#include "esp_err.h"
#include "esp_private/pm_impl.h"
#include "soc/rtc.h"
#include "soc/soc_caps.h"

int esp_pm_impl_get_cpu_freq(pm_mode_t mode)
{
    (void)mode;
    rtc_cpu_freq_config_t config;
    rtc_clk_cpu_freq_get_config(&config);
    return config.freq_mhz;
}

/*
 * "Skip light sleep" callback registry. In esp-idf this lives in pm_impl.c and
 * is consulted by the esp_pm automatic light-sleep loop. That loop does not run
 * under Zephyr (pm_impl.c is not compiled; Zephyr's pm_policy drives system
 * light sleep), so these are no-op stubs that only exist to satisfy the link.
 * Callers such as the BLE controller (CONFIG_ESP32_BT_LE_SLEEP_ENABLE) instead
 * coordinate with light sleep through a pm_policy state lock taken around radio
 * activity, so the registered callback would never be invoked here anyway.
 */
esp_err_t esp_pm_register_skip_light_sleep_callback(skip_light_sleep_cb_t cb)
{
    (void)cb;
    return ESP_OK;
}

esp_err_t esp_pm_unregister_skip_light_sleep_callback(skip_light_sleep_cb_t cb)
{
    (void)cb;
    return ESP_OK;
}

#if SOC_VBAT_SUPPORTED
#include "esp_vbat.h"

esp_vbat_state_t esp_vbat_get_battery_state(void)
{
    return ESP_VBAT_STATE_NORMAL;
}
#endif
