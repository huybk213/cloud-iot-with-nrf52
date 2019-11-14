/*
 * Copyright 2019 Ravikiran Bukkasagara <contact@ravikiranb.com>
 *        
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *    
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "bsp.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_rng.h"
#include "nrf_uarte.h"
#include "nrfx_prs.h"
#include "nrfx_rtc.h"
#include "nrfx_uarte.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "at_modem.h"
#include "temp_sensor.h"
#include "timer_interface.h"
#include "uart_print.h"

#include "sim7600_gprs.h"

#define LED_BLUE 0
#define LED_GREEN 1

static void halt_error(void);
static void rtc_init_for_timers(void);

extern int aws_iot_app(void);
extern int gcp_iot_app(void);

static const char* ntp_servers[] = {
    "time.google.com",
    "time-a.nist.gov",
    "time-b.nist.gov",
    "time-c.nist.gov",
    NULL,
};

static void halt_error(void)
{

    bsp_board_led_on(LED_BLUE);
#ifdef DEBUG
    at_dump_buffer();
#endif
    while (true) {
        // Do nothing.
    }
}

static void rtc1_handler(nrfx_rtc_int_type_t type)
{
    (void)type;
}

static void rtc_init_for_timers(void)
{
    nrfx_err_t ret;
    nrfx_rtc_t rtc = NRFX_RTC_INSTANCE(1);
    nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;

    ret = nrfx_rtc_init(&rtc, &config, rtc1_handler);
    if (ret != NRFX_SUCCESS)
        halt_error();

    //disable all rtc interrupts.
    nrfx_rtc_int_disable(&rtc, &ret);

    nrfx_rtc_enable(&rtc);

    //from this point onwards only HAL counter register reads.
}

int main(void)
{
    int ret;
    gprs_network_mode_t network_mode;
    int i;

    nrf_drv_clock_init();

    nrf_drv_clock_hfclk_request(NULL);

    while (!nrf_drv_clock_hfclk_is_running())
        ;

    //LFCLK synthesized from HFXO HF CLK.
    nrf_drv_clock_lfclk_request(NULL);

    while (!nrf_drv_clock_lfclk_is_running())
        ;

    bsp_board_init(BSP_INIT_LEDS);

    bsp_board_led_on(LED_GREEN);
    bsp_board_led_off(LED_BLUE);

    rtc_init_for_timers();

    ret = nrf_drv_rng_init(NULL);
    if (ret != NRF_SUCCESS)
        halt_error();

    temps_init();

    console_init();

    dbg_printf(DEBUG_LEVEL_INFO, "\r\n\r\nDebug Console\r\n\r\n");

    ret = gprs_init(0, 0);
    if (ret < 0) {
        dbg_printf(DEBUG_LEVEL_ERROR, "gprs_init: %d\r\n", ret);
        halt_error();
    }

    ret = gprs_get_network_mode(&network_mode);
    if (ret < 0) {
        dbg_printf(DEBUG_LEVEL_ERROR, "gprs_get_network_mode: %d\r\n", ret);
        halt_error();
    }

    dbg_printf(DEBUG_LEVEL_INFO, "Network mode=%d\r\n", network_mode);

    ret = gprs_ssl_init();
    if (ret < 0) {
        dbg_printf(DEBUG_LEVEL_ERROR, "gprs_ssl_init: %d\r\n", ret);
        halt_error();
    }

    //NTP sync
    for (i = 0; ntp_servers[i] != NULL; i++) {
        ret = gprs_ntp_sync(ntp_servers[i], TIME_ZONE_CODE_CURRENT);

        if (ret < 0) {
            dbg_printf(DEBUG_LEVEL_ERROR, "gprs_ntp_sync failed: %s, %d\r\n", ntp_servers[i], ret);
        } else
            break;
    }

    if (ntp_servers[i] == NULL) {
        dbg_printf(DEBUG_LEVEL_ERROR, "NTP sync failed\r\n");
        halt_error();
    }

#ifdef USE_AWS_IOT_CORE
    ret = aws_iot_app();
    if (ret < 0) {
        dbg_printf(DEBUG_LEVEL_ERROR, "aws_iot_simple: %d\r\n", ret);
        halt_error();
    }
#else
    ret = gcp_iot_app();
    if (ret < 0) {
        dbg_printf(DEBUG_LEVEL_ERROR, "gcp_iot_simple: %d\r\n", ret);
        halt_error();
    }
#endif

    while (1)
        ;
}
