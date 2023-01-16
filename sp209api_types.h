#ifndef SP209API_TYPES_H
#define SP209API_TYPES_H

#include <stdint.h>
#include "ihwapi_common_types.h"

#if defined(GENERATE_API_WIN)
#define SCANA_API __declspec(dllexport)
#elif defined(GENERATE_API_UNIX)
#define SCANA_API __attribute__((visibility("default")))
#elif defined(GENERATE_API_MAC)
#include "ftd2xxUNIX.h"
#include "WinTypes.h"
#define SCANA_API __attribute__((visibility("default")))
#elif defined(OS_WIN)
#define SCANA_API __declspec(dllimport)
#else
#define SCANA_API
#endif

#define API_VER_MAJ 2
#define API_VER_MIN 0
#define API_VER_PAT 0

#define SP209_CHANNELS_COUNT (9)
#define SP209_TRIG_ENGINES_COUNT (2)
#define SP209_THRESHOLDS_COUNT (3)
#define SP209_MAX_TRIG_STEPS_COUNT (128)


/**
 * @brief sp209api_handle Pointer to SP209API
 */
typedef void* sp209api_handle;





/**
 * @brief The sp209api_variant_t enum is used to determine which firmware is loaded when openning a device
 */
enum sp209api_variant_t
{
    SP209API_VARIANT_STD = 0,   ///< Standard SP209 firmware
    SP209API_VARIANT_NEXUS = 1, ///< Custom firmware reserved for Nexus bus analyzer
    SP209API_VARIANT_TPIU = 2,  ///< Custom firmware reserved for TPIU bus analyzer
};

/**
 * @brief The sp209api_clock_pol_t enum defines the clock polarity
 * of the external clock (if used)
 */
enum sp209api_clock_pol_t
{
    CLK_POL_RISING = 1,  ///< Rising edge
    CLK_POL_FALLING = 0, ///< Falling edge
    CLK_POL_DUAL = 2,    ///< Dual edge (any rising or falling edge)
};

/**
 * @brief The sp209api_device_model_t enum defines the model of the device within SP209 family
 * of logic analyzer devices
 */
enum sp209api_device_model_t
{
    SP209API_MODEL_NONE = 0,   ///< Should never be used.
    SP209API_MODEL_209 = 360,  ///< Standard SP209
    SP209API_MODEL_209I = 370, ///< Industrial SP209i
};

/**
 * @brief The sp209api_threshold_t enum defines the thresholds supported by SP209 devices
 */
enum sp209api_threshold_t
{
    SP209API_TH_1V8 = 0,   ///< 1.8V logic level
    SP209API_X_TH_2V5 = 1, ///< 2.5V logic level
    SP209API_X_TH_3V3 = 2, ///< 3.3V logic level
    SP209API_TH_5V0 = 4,   ///< 5.0V logic level
};

/**
 * @brief The sp209api_trigger_type_t enum lists the different kind of trigger supported by the API
 */
enum sp209api_trigger_type_t
{
    SP209API_TRG_NOTRIG = 0,
    SP209API_TRG_RISING,
    SP209API_TRG_FALLING,
    SP209API_TRG_CHANGE,
    SP209API_TRG_EXT_RISING,
    SP209API_TRG_EXT_FALLING
};

#pragma pack(push, 4) //Ensure known packing on all platforms

struct sp209api_trigger_description_t
{
    /**
     * @brief type is the type of trigger (e.g. falling edge, rising edge or logic change).
     */
    sp209api_trigger_type_t type;
    /**
     * @brief channel set to the number of the channel concerned by the trigger,
     * or -1 if you wish to target all channels. (-1 is only valid for Logic Change
     * type of trigger)
     * @note channel is a 0 based index, i.e. first channel is 0.
     */
    int8_t channel;
};

/**
 * @brief The spx_settings_t struct exposes the options that need to be configured by the user via
 * various GUI options.
 */
struct sp209api_settings_t
{
    /**
     * @brief Total number of samples requested by the user
     */
    int64_t sampling_depth;

    /**
     * @brief Total number of samples after the trigger
     */
    int64_t post_trig_depth;

    /**
     * @brief Trigger clock expressed in HZ
     */
    uint32_t t_clk[SP209_TRIG_ENGINES_COUNT];

    /**
     * @brief An array of thresholds
     * @details can be 3, 6, or 12, for SP209, SP218, and SP236
     */
    sp209api_threshold_t thresh_cfg[SP209_THRESHOLDS_COUNT];

    /**
     * @brief enable the use of external (AKA State mode)
     */
    bool ext_clk;

    /**
     * @brief External clock polarity (active edge selection)
     */
    sp209api_clock_pol_t ext_clk_pol;

    /**
     * @brief activate the 50R input resistor on Ext. Trig input
     */
    bool ext_trig_50r;

    /**
     * @brief enable (and use) Ext Trig In as trigger source
     */
    bool ext_trig_in[SP209_TRIG_ENGINES_COUNT];

    /**
     * @brief ext_trig_in_polarity selects the active edge for the external trigger
     * 0: Faling edge
     * 1: Rising edge
     */
    uint8_t ext_trig_in_polarity[SP209_TRIG_ENGINES_COUNT];
    uint8_t ext_trig_out_polarity;

    /**
     * @brief 2 bits describing the operation of the dual trigger engine
     * @details the 2 LSB bits describe the operation of the dual trigger engine
     * as the following:
     * - 00: Trig 0 or Trig 1 (any of the two trigger engines will cause the trigger to be valid)
     * - 01: Trig 0 then Trig 1 (Trig 1 is only enabled after Trig 1 occures)
     * - 10: Trig 1 then Trig 0 (Trig 0 is only enabled after Trig 0 occures)
     * - 11: Trig 0 and Trig 1, in any order.
     */
    uint8_t trig_order;

    //********
    //Industrial version (SP209I) only related settings
    //********

    /**
     * @brief Multiplexing enable for each pin
     * @details when enabled an input pin uses the multiplexed (auxiliary input)
     * instead of the standard single ended input.
     * @note This is only applicable to SP209i (industrial) version
     */
    bool mux[SP209_CHANNELS_COUNT];
    /**
     * @brief can_term when TRUE, CAN bus termination resistor is enabled
     * @note This is only applicable to SP209i (industrial) version
     */
    bool can_term;
    /**
     * @brief rs485_1_term when TRUE, RS485 bus number 1's termination resistor is enabled
     * @note This is only applicable to SP209i (industrial) version
     */
    bool rs485_1_term;
    /**
     * @brief rs485_2_term when TRUE, RS485 bus bumber 2's termination resistor is enabled
     * @note This is only applicable to SP209i (industrial) version
     */
    bool rs485_2_term;
};

/**
 * @brief The sp209api_transition_t struct describes an SP209 transition
 * @details SP209 API provides captured samples in minimal structures called "transition".
 * During a transition, a chanel's logic level change. This structure describes this
 * transition.
 */
struct sp209api_trs_t
{
    uint8_t value; //Line value
    /**
     * @brief delta_samples Number of samples since the previous transition
     */
    int64_t sampple_index; //index of the same associated with that transition
};


#pragma pack(pop)

#endif // SP209API_TYPES_H
