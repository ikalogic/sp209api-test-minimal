#ifndef DEVICE_TYPE_H
#define DEVICE_TYPE_H

/**
 * @brief The ihwapi_err_code_t enum
 */
enum ihwapi_err_code_t
{
    IHWAPI_OK = 0, ///< All is OK
    IHWAPI_BUSY,///< Device is busy
    IHWAPI_INVALID_ARGUMENT, ///< One or more invalid arguments were used when calling an API function
    IHWAPI_DEVICE_NOT_FOUND, ///< Device not found
    IHWAPI_DEVICE_NOT_OPEN, ///< Device is not open
    IHWAPI_INVALID_HANLDE, ///< invalid Handle is used
    IHWAPI_DEVICE_ALREADY_OPEN, ///< Device is already open
    IHWAPI_DEVICE_ERROR, ///< Hardware error in the device hardware
    IHWAPI_FIRMWARE_ERROR, ///< Firmware error (invalid version or corrupted image)
    IHWAPI_FIRMWARE_UPDATE_ERROR, ///< Error during firmware update
    IHWAPI_DESCROPTOR_MISMATCH, ///< Device descritor does not match actual device
    IHWAPI_DEVICE_ACTIVATION_ERROR, ///< An error occured while activating the device
    IHWAPI_UNKNOWN_ERROR,///< Unknown error
    IHWAPI_NOT_SUPPORTED, ///< Unsopported command by this device
};

/**
 * @brief The device_descriptor_t struct defines any device detected by the API
 */
struct device_descriptor_t
{
    /**
     * @brief sn pointer to Null terminated string for the serial number
     */
    char* sn;
    /**
     * @brief desc pointer to Null terminated string for the descriptions of the device
     */
    char* desc;
};

#endif // DEVICE_TYPE_H
