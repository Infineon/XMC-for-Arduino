#ifndef ONEWIRE_CONF_H
#define ONEWIRE_CONF_H

#include <SPI.h>

namespace onewire {
	
#if defined(XMC1100_XMC2GO)
#define NUM_ONEWIRE_HW  			4
#define PIN_HAS_ONEWIRE_HW(pin)		( (pin==0) || (pin==1) || (pin==10) || (pin==11) )
#define PIN_TO_ONEWIRE_HW(pin)		( (pin==0)?0: ((pin==1)?1: ((pin==10)?2: ((pin==11)?3: -1 ))))

XMC_SPI_t mappingHW[] = 
{
	{	//DONE tested with -O0
		.channel          = XMC_SPI0_CH1,
		.channel_config   = {
			.baudrate = 15984375U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)6
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)6
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.input_source     = XMC_INPUT_C,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)6
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		}
	},
	{
		.channel          = XMC_SPI0_CH1,
		.channel_config   = {
			.baudrate = 15984375U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)7
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)7
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.input_source     = XMC_INPUT_D,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)7
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		}
	},
	{
		.channel          = XMC_SPI0_CH1,
		.channel_config   = {
			.baudrate = 15984375U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)11
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)11
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.input_source     = XMC_INPUT_F,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)11
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		}
	},
	{
		.channel          = XMC_SPI0_CH1,
		.channel_config   = {
			.baudrate = 15984375U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)10
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)10
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.input_source     = XMC_INPUT_E,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)10
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		}
	}
};

#elif defined(XMC1100_Boot_Kit)
#define NUM_ONEWIRE_HW  			3
#define PIN_HAS_ONEWIRE_HW(pin)		( (pin==11) || (pin==15) || (pin==16) )
#define PIN_TO_ONEWIRE_HW(pin)		( (pin==11)?0: ((pin==15)?1: ((pin==16)?2: -1 )))


XMC_SPI_t mappingHW[] =
{
	{
		.channel          = XMC_SPI0_CH0,
		.channel_config   = {
			.baudrate = 15984375U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT1_BASE,
			.pin  = (uint8_t)1
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT1_BASE,
			.pin  = (uint8_t)1
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.input_source     = XMC_INPUT_D,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT1_BASE,
			.pin  = (uint8_t)1
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		}
	},
	{
		.channel          = XMC_SPI0_CH0,
		.channel_config   = {
			.baudrate = 15984375U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)1
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)1
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.input_source     = XMC_INPUT_F,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)1
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		}
	},
	{
		.channel          = XMC_SPI0_CH0,
		.channel_config   = {
			.baudrate = 15984375U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)0
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)0
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		},
		.input_source     = XMC_INPUT_E,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)0
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
		}
	}
};

#elif defined(XMC4700_Relax_Kit)
#define NUM_ONEWIRE_HW  			6
#define PIN_HAS_ONEWIRE_HW(pin)		( (pin==1) || (pin==15) || (pin==29) || (pin==37) || (pin==70) || (pin==88) )
#define PIN_TO_ONEWIRE_HW(pin)		( (pin==1)?0: ((pin==15)?1: ((pin==29)?2: ((pin==37)?3: ((pin==70)?4: ((pin==88)?5: -1 ))))))

XMC_SPI_t mappingHW[] =
{
	{	//DONE tested with -O0
		.channel          = XMC_SPI1_CH0,
		.channel_config   = {
			.baudrate = 20003906U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)14
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)14
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
		},
		.input_source     = XMC_INPUT_B,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT2_BASE,
			.pin  = (uint8_t)14
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
	},
	{
		.channel          = XMC_SPI1_CH1,
		.channel_config   = {
			.baudrate = 20003906U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)15
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)15
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
		},
		.input_source     = XMC_INPUT_A,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)15
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
	},
	{
		.channel          = XMC_SPI2_CH1,
		.channel_config   = {
			.baudrate = 20003906U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)5
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)5
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
		},
		.input_source     = XMC_INPUT_A,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)5
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
	},
	{
		.channel          = XMC_SPI1_CH0,
		.channel_config   = {
			.baudrate = 20003906U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)5
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)5
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
		},
		.input_source     = XMC_INPUT_B,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
			.pin  = (uint8_t)5
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
	},
	{
		.channel          = XMC_SPI0_CH1,
		.channel_config   = {
			.baudrate = 20003906U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)13
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)13
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
		},
		.input_source     = XMC_INPUT_D,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT3_BASE,
			.pin  = (uint8_t)13
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
	},
	{
		.channel          = XMC_SPI2_CH0,
		.channel_config   = {
			.baudrate = 20003906U,
			.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
			.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		},
		.mosi             = {
			.port = (XMC_GPIO_PORT_t*)PORT5_BASE,
			.pin  = (uint8_t)0
		},
		.mosi_config      = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
		.miso             = {
			.port = (XMC_GPIO_PORT_t*)PORT5_BASE,
			.pin  = (uint8_t)0
		},
		.miso_config      = {
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
		},
		.input_source     = XMC_INPUT_B,
		.sclkout = {
			.port = (XMC_GPIO_PORT_t*)PORT5_BASE,
			.pin  = (uint8_t)0
		},
		.sclkout_config   = {
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		},
	}
};
#else
// unknown device used
#define NUM_ONEWIRE_HW  			0
#define PIN_HAS_ONEWIRE_HW(pin)		0
#define PIN_TO_ONEWIRE_HW(pin)		-1

XMC_SPI_t mappingHW[1];
#endif
	
}	/* namespace onewire */
#endif