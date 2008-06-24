/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 *   Copyright (C) 2007 John Crispin <blogic@openwrt.org> 
 */

#ifndef _IFXMIPS_GPIO_H_
#define _IFXMIPS_GPIO_H_

#include <asm/ifxmips/ifxmips.h>
#include <asm/ifxmips/ifxmips_gpio.h>

static inline int
gpio_direction_input(unsigned gpio)
{
	ifxmips_port_set_dir_in(0, gpio);
	return 0;
}

static inline int
gpio_direction_output(unsigned gpio, int value)
{
	ifxmips_port_set_dir_out(0, gpio);
	return 0;
}

static inline int
gpio_get_value(unsigned gpio)
{
	ifxmips_port_get_input(0, gpio);
	return 0;
}

static inline void
gpio_set_value(unsigned gpio, int value)
{
	ifxmips_port_set_output(0, gpio);
}

static inline int
gpio_request(unsigned gpio, const char *label)
{
	return 0;
}

static inline void
gpio_free(unsigned gpio)
{
}

static inline int
gpio_to_irq(unsigned gpio)
{
	return 0;
}

static inline int
irq_to_gpio(unsigned irq)
{
	return 0;
}

static inline int
gpio_cansleep(unsigned gpio)
{
        return 0;
}

static inline int
gpio_get_value_cansleep(unsigned gpio)
{
        might_sleep();
        return gpio_get_value(gpio);
}

static inline void
gpio_set_value_cansleep(unsigned gpio, int value)
{
        might_sleep();
        gpio_set_value(gpio, value);
}
#endif
