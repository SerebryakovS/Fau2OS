/*
 * Abicom International Scorpion SC450 support.
 *
 * Copyright (c) 2012 Qualcomm Atheros
 * Copyright (c) 2012-2013 Gabor Juhos <juhosg@openwrt.org>
 * Copyright (c) 2017 Conor O'Gorman <i@conorogorman.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <linux/platform_device.h>
#include <linux/platform_data/phy-at803x.h>

#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "pci.h"
#include "dev-ap9x-pci.h"
#include "dev-gpio-buttons.h"
#include "dev-eth.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-nfc.h"
#include "dev-usb.h"
#include "dev-wmac.h"
#include "machtypes.h"

#define SC450_GPIO_LED_POWER		13
#define SC450_GPIO_LED_ERR1		14
#define SC450_GPIO_LED_ERR2		15
#define SC450_GPIO_LED_WLAN		16
#define SC450_GPIO_BTN_RESET		17
#define SC450_GPIO_WP			18
#define SC450_GPIO_POE			19
#define SC450_GPIO_RX_LOS		20
#define SC450_GPIO_MOD_GND		21
#define SC450_GPIO_MOD_SCL		22
#define SC450_GPIO_MOD_SDA		23

#define SC450_KEYS_POLL_INTERVAL	20	/* msecs */
#define SC450_KEYS_DEBOUNCE_INTERVAL	(3 * SC450_KEYS_POLL_INTERVAL)

#define SC450_MAC0_OFFSET		0
#define SC450_MAC1_OFFSET		6
#define SC450_WMAC_CALDATA_OFFSET	0x1000
#define SC450_PCIE_CALDATA_OFFSET	0x5000

static struct gpio_led sc450_leds_gpio[] __initdata = {
	{
		.name		= "sc450:green:power",
		.gpio		= SC450_GPIO_LED_POWER,
		.active_low	= 1,
	},
	{
		.name		= "sc450:red:power",
		.gpio		= SC450_GPIO_LED_ERR1,
		.active_low	= 1,
	},
	{
		.name		= "sc450:green:wlan",
		.gpio		= SC450_GPIO_LED_WLAN,
		.active_low	= 1,
	},
	{
		.name		= "sc450:red:wlan",
		.gpio		= SC450_GPIO_LED_ERR2,
		.active_low	= 1,
	}
};

static struct gpio_keys_button sc450_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = SC450_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= SC450_GPIO_BTN_RESET,
		.active_low	= 1,
	}
};

static struct at803x_platform_data at803x_data = {
	.disable_smarteee = 1,
	.enable_rgmii_rx_delay = 0,
	.enable_rgmii_tx_delay = 0,
};

static struct mdio_board_info sc450_mdio0_info[] = {
	{
		.bus_id = "ag71xx-mdio.0",
		.mdio_addr = 1,
		.platform_data = &at803x_data,
	},
};

static void __init sc450_setup(void)
{
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);

	ath79_register_m25p80(NULL);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(sc450_leds_gpio),
				 sc450_leds_gpio);
	ath79_register_gpio_keys_polled(-1, SC450_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(sc450_gpio_keys),
					sc450_gpio_keys);

	ath79_register_usb();
	ath79_register_nfc();

	ath79_register_wmac(art + SC450_WMAC_CALDATA_OFFSET, NULL);

	ath79_register_mdio(0, 0);
	mdiobus_register_board_info(sc450_mdio0_info,
				    ARRAY_SIZE(sc450_mdio0_info));

	ath79_init_mac(ath79_eth0_data.mac_addr, art + SC450_MAC0_OFFSET, 0);

	ath79_eth0_pll_data.pll_1000 = 0xa6000101;
	ath79_eth0_pll_data.pll_100 = 0xa4000101;
	/* GMAC0 is connected to the RMGII interface */
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_RGMII;
	ath79_eth0_data.phy_mask = 0xF;
	ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;

	ath79_register_eth(0);

	/* GMAC1 is connected to the SGMII interface */
	ath79_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
	ath79_eth1_data.speed = SPEED_1000;
	ath79_eth1_data.duplex = DUPLEX_FULL;

	ath79_register_eth(1);

	ath79_register_pci();
}

MIPS_MACHINE(ATH79_MACH_SC450, "SC450", "Abicom SC450", sc450_setup);
