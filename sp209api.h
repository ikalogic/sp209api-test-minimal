#ifndef SP209_API_H
#define SP209_API_H

#if defined(GENERATE_API_WIN)
    #define SCANA_API __declspec(dllexport)
#elif defined(GENERATE_API_UNIX)
    #define SCANA_API __attribute__((visibility("default")))
#elif defined(GENERATE_API_MAC)
    #include "ftd2xxUNIX.h"
    #include "WinTypes.h"
    #  define SCANA_API __attribute__((visibility("default")))
#elif defined(OS_WIN)
    #define SCANA_API __declspec(dllimport)
#else
    #define SCANA_API
#endif

#include <cstddef>
#include "ihwapi_common_types.h"
#include "sp209api_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief sp209api_handle Pointer to SP209API
 */
typedef void* sp209api_handle;

//library instance management

/**
 * @brief sp209api_create_new_handle This functions creates a new handle that can be
 * later used to call the functions of this API.
 * @return the newly created handle.
 */
SCANA_API
sp209api_handle sp209api_create_new_handle(void);

/**
 * @brief sp209api_free is used to clear a handle (freeing all the memory used).
 * @param handle
 */
SCANA_API
void sp209api_free(sp209api_handle handle);


//Device listing functions

/**
 * @brief sp209api_create_device_list is used to create (or update the list
 * of SP209 devices that can be found on the USB).
 * @param handle
 */
SCANA_API
void sp209api_create_device_list(sp209api_handle handle);

/**
 * @brief sp209api_free_device_list is used to free the memory used to
 * store the list of current devices.
 * @param handle
 */
SCANA_API
void sp209api_free_device_list(sp209api_handle handle);

/**
 * @brief sp209api_get_devices_count is used to get the list of device
 * that was created using the sp209api_create_device_list function.
 * @param handle
 * @return the number of devices
 */
SCANA_API
uint8_t sp209api_get_devices_count(sp209api_handle handle);

/**
 * @brief sp209api_get_device_descriptor is used to get the device descriptor
 * for a device on the bus. The funciton sp209api_create_device_list must be called
 * prior to calling this function. The device descriptor is needed to open an SP209
 * device.
 * @param handle
 * @param device_number, 0-based index.
 * @return device descriptor (Serial number and description). See device_descriptor_t type.
 */
SCANA_API
device_descriptor_t sp209api_get_device_descriptor(sp209api_handle handle, uint8_t device_number);

//General Device Commands (common to all variants)

/**
 * @brief sp209api_device_open Open SP209 device using a device descriptor.
 * @param handle
 * @param device: the device descriptor
 * @param variant: the device variant (or operation mode). Some devices ship with custom,
 * application speicifc firmware (like Nexus or TPIU) that are loaded next to the standard (Logic Analyzer)
 * firmware. The variant must be specified when openning a device.
 * @return error code, see ihwapi_err_code_t type.
 */
SCANA_API
ihwapi_err_code_t sp209api_device_open(sp209api_handle handle, device_descriptor_t device, sp209api_variant_t variant);

/**
 * @brief sp209api_device_power_off is used to switch off SP209 device (effectively
 * loosing any configuration made to the device).
 * @param handle
 * @return error code, see ihwapi_err_code_t type.
 */
SCANA_API
ihwapi_err_code_t sp209api_device_power_off(sp209api_handle handle);

/**
 * @brief sp209api_get_firmware_version_major returns the major version of the firmware
 * @param handle
 * @return
 */
SCANA_API
uint8_t sp209api_get_firmware_version_major(sp209api_handle handle);

/**
 * @brief sp209api_get_firmware_version_minor returns the minor version of the firmware
 * @param handle
 * @return
 */
SCANA_API
uint8_t sp209api_get_firmware_version_minor(sp209api_handle handle);

/**
 * @brief sp209api_get_bootloader_version_major return the major version of the bootloader
 * @param handle
 * @return
 */
SCANA_API
uint8_t sp209api_get_bootloader_version_major(sp209api_handle handle);

/**
 * @brief sp209api_get_bootloader_version_minor returns the minor version of the bootloader
 * @param handle
 * @return
 */
SCANA_API
uint8_t sp209api_get_bootloader_version_minor(sp209api_handle handle);

/**
 * @brief sp209api_get_device_open_flag returns TRUE if the device is open (connection is still active)
 * @param handle
 * @return
 */
SCANA_API
bool sp209api_get_device_open_flag(sp209api_handle handle);

/**
 * @brief sp209api_launch_fw_update is used to launch a firmware update
 * @param handle
 * @param fw_data a pointer to the an array containing the firmware (loaded from *.bin file)
 * @param fw_size the size of the array (number of bytes).
 * @return error code, see ihwapi_err_code_t type.
 */
SCANA_API
ihwapi_err_code_t sp209api_launch_fw_update(sp209api_handle handle, uint8_t *fw_data, size_t fw_size);

/**
 * @brief sp209api_request_abort request any pending operation to abort.
 * This function returns without verifying if the operation was effectiely aborted
 * @param handle
 */
SCANA_API
void sp209api_request_abort(sp209api_handle handle);

/**
 * @brief sp209api_get_firmware_update_progress is used to get the progres of an ongoing
 * firmware update running in background.
 * @param handle
 * @return Number from 0 to 100 representing progress.
 */
SCANA_API
uint8_t sp209api_get_firmware_update_progress(sp209api_handle handle);

/**
 * @brief sp209api_get_firmware_update_done_flag is used to poll firmware update status
 * @param handle
 * @return true if done, false otherwize.
 */
SCANA_API
bool sp209api_get_firmware_update_done_flag(sp209api_handle handle);

/**
 * @brief sp209api_get_last_error_code is used to return the last error code.
 * It should be called after a background task is finished.
 * @note After the first call to this function, the error flag will be reset to default "no error" value.
 * @param handle
 * @return error code.
 */
SCANA_API
ihwapi_err_code_t sp209api_get_last_error_code(sp209api_handle handle);


/**
 * @brief sp209api_launch_new_capture is used to start a new capture of samples.
 * @param handle
 * @param settings the SP209 device settings to be used for this capture
 * @return error code.
 * @details This function does not offer any trigger options, capture will start as soon as possible
 * after this function is called.
 * @see sp209api_launch_new_capture_complex_trigger
 */
SCANA_API
ihwapi_err_code_t sp209api_launch_new_capture_simple_trigger(sp209api_handle handle,
                                                              sp209api_trigger_description_t trig,
                                                              sp209api_settings_t settings);

/**
 * @brief sp209api_launch_new_capture_complex_trigger is used to start a new capture
 * after a specific trigger condition occured.
 * @warning This functions is not intended to be used by anything/anyone else but ScanaStudio software
 * @details Trigger is defined using trigger steps. A trigger step mainly describes the logic state
 * of all channels and timing constraints with respect to previous step. Each step is a coded as a 64 bits word.
 * For a capture to start, all the logic signals must match all trigger steps in
 * the right order.
 *
 * SO209 has two trigger engines (named A and B).
 * @param handle
 * @param settings the SP209 device settings to be used for this capture
 * @param trig_a_data pointer to an array of trigger steps (words), or null pointer if not used
 * @param trig_a_size number of steps pointed to by trig_a_data, or 0 if trig_a_data is a null pointer.
 * @param trig_b_data pointer to an array of trigger steps (words), or null pointer if not used
 * @param trig_b_size number of steps pointed to by trig_b_data, or 0 if trig_b_data is a null pointer.
 * @return error code.
 * @see sp209api_launch_new_capture_simple_trigger
 */
SCANA_API
ihwapi_err_code_t sp209api_launch_new_capture_complex_trigger(sp209api_handle handle,
                                              sp209api_settings_t settings,
                                              uint64_t* trig_a_data, uint16_t trig_a_size,
                                              uint64_t* trig_b_data, uint16_t trig_b_size);

/**
 * @brief sp209api_get_config_done_flag is used to check if the device have finished its internal
 * configuration after a request to launch a new capture.
 * @details There is no any obligation to use this function, as the configuration of the device
 * usually takes a few milliseconds. This function is mainly here for feedback and monitoring purposes.
 * @param handle
 * @return TRUE if configuration is done, FALSE if configuration is still in progress.
 */
SCANA_API
bool sp209api_get_config_done_flag(sp209api_handle handle);

/**
 * @brief sp209api_get_available_transitions
 * @param handle
 * @return
 */
SCANA_API
uint32_t sp209api_get_available_transitions(sp209api_handle handle);

SCANA_API
void sp209api_get_transitions(sp209api_handle handle, sp209api_transition_t* transitions_data, uint32_t transitions_to_get);

SCANA_API
void sp209api_flush_transitions(sp209api_handle handle);

SCANA_API
bool sp209api_get_triggered_flag(sp209api_handle handle);


SCANA_API
bool sp209api_get_capture_done_flag(sp209api_handle handle);

//TPIU Variant functions
/**
 * @brief sp209api_tpiu_start is used to start the SP209 device in TPIU mode. Once started, SP209 device will stream captured TPIU packets
 * @param handle
 * @param test_mode: if true, the SP209 device will send 16 bit counter information instead of real captured TPIU data
 * @param logic_threshold
 * @return error code
 * @note The SP209 device must be open in TPIU operation mode (see sp209api_device_open).
 */
SCANA_API
ihwapi_err_code_t sp209api_tpiu_start(sp209api_handle handle,
                                      bool test_mode,
                                      sp209api_threshold_t logic_threshold);

/**
 * @brief sp209api_tpiu_stop is used to stop TPIU streaming.
 * @param handle
 */
SCANA_API
void sp209api_tpiu_stop(sp209api_handle handle);

/**
 * @brief sp209api_tpiu_get_available_data_count returns the number of TPIU data items that can be read.
 * @param handle
 * @return
 */
SCANA_API
uint32_t sp209api_tpiu_get_available_data_count(sp209api_handle handle);

/**
 * @brief sp209api_tpiu_get_data is used to fill "data_to_get" items of data in "*data" buffer.
 * @note *data must be initialized with the correct size prior to calling this functions
 * @param handle
 * @param data
 * @param data_to_get
 */
SCANA_API
void sp209api_tpiu_get_data(sp209api_handle handle, sp209api_tpiu_data_t* data, uint32_t data_to_get);

/**
 * @brief sp209api_tpiu_flush_data is used to flush any data that was streamed by SP209 device but still
 * not retrieved by the application.
 * @param handle
 */
SCANA_API
void sp209api_tpiu_flush_data(sp209api_handle handle);

/**
 * @brief tpiu_get_overflow_flag is used to check if an overflow has occured in the SP209 DDR3 memory since last "tpiu start".
 * @param handle
 * @return
 */
SCANA_API
bool sp209api_get_overflow_flag(sp209api_handle handle);



#ifdef __cplusplus
}
#endif


#endif // SP209_API_H
