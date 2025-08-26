#include "SPI.h"
#include <stdlib.h>

void *operator new(size_t size) { return malloc(size); }

void operator delete(void *ptr) noexcept { free(ptr); }

#if !defined(USE_SW_SPI)
    #include "Wire.h"

    // swap SPI_default and SPI_for_xmc_SD if desired by user
    #if defined(USE_XMC_RELAX_KIT_SD) && defined(XMC_SPI_for_xmc_SD)
XMCSPIClass SPI(&XMC_SPI_default);
XMCSPIClass SPI1(&XMC_SPI_for_xmc_SD);
    #else // normal behaviour
XMCSPIClass SPI(&XMC_SPI_default);
        #if (NUM_SPI > 1)
XMCSPIClass SPI1(&XMC_SPI_1);
        #endif
    #endif
uint8_t SS = PIN_SPI_SS;
uint8_t MOSI = PIN_SPI_MOSI;
uint8_t MISO = PIN_SPI_MISO;
uint8_t SCK = PIN_SPI_SCK;

    #if (NUM_SPI > 2)
XMCSPIClass SPI2(&XMC_SPI_2);
        #if (NUM_SPI > 3)
XMCSPIClass SPI3(&XMC_SPI_3);
            #if (NUM_SPI > 4)
XMCSPIClass SPI4(&XMC_SPI_4);
            #endif
        #endif
    #endif

//****************************************************************************
// @Local Functions
//****************************************************************************

// Public Methods //////////////////////////////////////////////////////////////
XMCSPIClass::XMCSPIClass(XMC_SPI_t *conf)
    : XMC_SPI_config(conf),
      initialized(false),
      interruptMode(SPI_IMODE_NONE),
      interruptSave(0),
      interruptMask(0) {}

XMCSPIClass::~XMCSPIClass() { end(); }

void XMCSPIClass::begin() {
    // Check if desire USIC channel is already in use
    if ((XMC_SPI_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_I2C) {
        Wire.end();
    }

    init();

    setBitOrder(_settings.getBitOrder());

    setDataMode(_settings.getDataMode());

    XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, _settings.getClockFreq());
}

void XMCSPIClass::init() {
    if (initialized) {
        return;
    }

    /* LLD initialization */
    XMC_SPI_CH_Init(XMC_SPI_config->channel, &(XMC_SPI_config->channel_config));

    /* Configure the data input line selected */
    XMC_SPI_CH_SetInputSource(XMC_SPI_config->channel, XMC_SPI_CH_INPUT_DIN0,
                              (uint8_t)XMC_SPI_config->input_source);

    /* Start the SPI_Channel */
    XMC_SPI_CH_Start(XMC_SPI_config->channel);

    /* Initialize SPI SCLK out pin */
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)XMC_SPI_config->sclkout.port,
                  (uint8_t)XMC_SPI_config->sclkout.pin, &(XMC_SPI_config->sclkout_config));

    /* Configure the input pin properties */
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)XMC_SPI_config->miso.port, (uint8_t)XMC_SPI_config->miso.pin,
                  &(XMC_SPI_config->miso_config));

    /* Configure the output pin properties */
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)XMC_SPI_config->mosi.port, (uint8_t)XMC_SPI_config->mosi.pin,
                  &(XMC_SPI_config->mosi_config));

    interruptMode = SPI_IMODE_NONE;
    interruptSave = 0;
    interruptMask = 0;
    initialized = true;
}

void XMCSPIClass::end() {
    // Only disable HW when USIC is used for SPI
    if ((XMC_SPI_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_SPI) {
        XMC_SPI_CH_Stop(XMC_SPI_config->channel);

        XMC_SPI_config->channel->DXCR[XMC_USIC_CH_INPUT_DX0] =
            (uint32_t)(XMC_SPI_config->channel->DXCR[XMC_USIC_CH_INPUT_DX0] |
                       (USIC_CH_DX0CR_DSEN_Msk)) &
            (~USIC_CH_DX0CR_INSW_Msk);
        XMC_USIC_CH_SetInputSource(XMC_SPI_config->channel, XMC_USIC_CH_INPUT_DX0, XMC_INPUT_A);
    }

    initialized = false;
}

// Function not used here
void XMCSPIClass::usingInterrupt(int interruptNumber) {}

void XMCSPIClass::notUsingInterrupt(int interruptNumber) {}

void XMCSPIClass::beginTransaction(arduino::SPISettings settings) {
    // Check if desire USIC channel is already in use
    if ((XMC_SPI_config->channel->CCR & USIC_CH_CCR_MODE_Msk) != XMC_USIC_CH_OPERATING_MODE_SPI) {
        SPI.begin();
    }
    _settings = settings;
    setBitOrder(settings.getBitOrder());
    setDataMode(static_cast<uint8_t>(settings.getDataMode()));
    XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, settings.getClockFreq());

    // TODO: Do sth with SS?
}

void XMCSPIClass::endTransaction(void) {
    // TODO: inTransactionFlag and interrupt not use
}

void XMCSPIClass::setBitOrder(BitOrder order) {
    if (order == LSBFIRST) {
        XMC_SPI_CH_SetBitOrderLsbFirst(XMC_SPI_config->channel);
    } else {
        XMC_SPI_CH_SetBitOrderMsbFirst(XMC_SPI_config->channel);
    }
}

void XMCSPIClass::setDataMode(uint8_t mode) {
    switch (mode) {
    case SPI_MODE0:
        // Low if inactive, transmit on falling clock, receive on raising clock edge
        XMC_SPI_CH_ConfigureShiftClockOutput(
            XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_ENABLED,
            XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
        break;

    case SPI_MODE1:
        // Low if inactive, transmit on rising clock, receive on falling clock edge
        XMC_SPI_CH_ConfigureShiftClockOutput(
            XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED,
            XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
        break;

    case SPI_MODE2:
        // High if inactive, transmit on rising clock, receive on falling clock edge
        XMC_SPI_CH_ConfigureShiftClockOutput(
            XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_ENABLED,
            XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
        break;

    case SPI_MODE3:
        // High if inactive, transmit on falling clock, receive on raising clock edge
        XMC_SPI_CH_ConfigureShiftClockOutput(
            XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED,
            XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
        break;

    default:
        break;
    }
}

void XMCSPIClass::setClockDivider(uint8_t div) {
    switch (div) {
    case SPI_CLOCK_DIV2:
        XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 8000000U);
        break;

    case SPI_CLOCK_DIV4:
        XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 4000000U);
        break;

    case SPI_CLOCK_DIV8:
        XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 2000000U);
        break;

    case SPI_CLOCK_DIV16:
        XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 1000000U);
        break;

    case SPI_CLOCK_DIV32:
        XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 500000U);
        break;

    case SPI_CLOCK_DIV64:
        XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 250000U);
        break;

    case SPI_CLOCK_DIV128:
        XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 125000U);
        break;

    default:
        break;
    }
}

byte XMCSPIClass::transfer(uint8_t data_out) {
    uint8_t data_in = 0;

    /* Clear RBF0 */
    (void)XMC_SPI_CH_GetReceivedData(XMC_SPI_config->channel);
    /* Clear RBF1 */
    (void)XMC_SPI_CH_GetReceivedData(XMC_SPI_config->channel);

    /*Sending a byte*/
    XMC_SPI_CH_Transmit(XMC_SPI_config->channel, data_out, XMC_SPI_CH_MODE_STANDARD);

    /*Wait till the byte has been transmitted*/
    while ((XMC_SPI_CH_GetStatusFlag(XMC_SPI_config->channel) &
            XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U)
        ;
    XMC_SPI_CH_ClearStatusFlag(XMC_SPI_config->channel,
                               XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);

    while (XMC_USIC_CH_GetReceiveBufferStatus(XMC_SPI_config->channel) == 0U)
        ;

    data_in = XMC_SPI_CH_GetReceivedData(XMC_SPI_config->channel);

    XMC_SPI_CH_ClearStatusFlag(XMC_SPI_config->channel,
                               ((uint32_t)XMC_SPI_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                (uint32_t)XMC_SPI_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION));

    return data_in;
}

void XMCSPIClass::transfer(void *buf, size_t count) {
    uint8_t *buffer = reinterpret_cast<uint8_t *>(buf);
    for (size_t index = 0; index < count; index++) {
        *buffer = transfer(*buffer);
        buffer++;
    }
}

uint16_t XMCSPIClass::transfer16(uint16_t data) {
    union {
        uint16_t val;

        struct {
            uint8_t lsb;
            uint8_t msb;
        };
    } data_in_out;

    // Split 16-bit word into two bytes:
    data_in_out.val = data;

    if (_settings.getBitOrder() == LSBFIRST) {
        data_in_out.lsb = transfer(data_in_out.lsb);
        data_in_out.msb = transfer(data_in_out.msb);
    } else {
        data_in_out.msb = transfer(data_in_out.msb);
        data_in_out.lsb = transfer(data_in_out.lsb);
    }

    // Combine the two received bytes into a 16-bit word:
    return data_in_out.val;
}

void XMCSPIClass::attachInterrupt() {
    // Should be enableInterrupt()
}

void XMCSPIClass::detachInterrupt() {
    // Should be disableInterrupt()
}

#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************