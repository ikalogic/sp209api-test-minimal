#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include "sp209api.h"

#define msleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

#define DEBUG_ENABLE (1)
#if DEBUG_ENABLE
    #define DBG   std::cout << std::endl
#else
    #define DBG if (0) std::cout
#endif

using namespace std;

int main()
{
    sp209api_handle h;
    device_descriptor_t d;
    ihwapi_err_code_t e = IHWAPI_DEVICE_NOT_OPEN;
    sp209api_settings_t settings;
    uint16_t devices_count = 0;
    int64_t samples_count = 0;
    int64_t post_trig_samples = 0;
    sp209api_trs_t trs;



    sp209api_create_new_handle(&h,sp209api_device_model_t::SP209API_MODEL_209I);
    sp209api_create_device_list(h);
    sp209api_get_devices_count(h,&devices_count);
    DBG << "Found " << devices_count << " devices" ;
    if (devices_count > 0)
    {
        sp209api_get_device_descriptor(h,0,&d);
        DBG << "New device, serial number = " << d.sn << ", description = " << d.desc ;
        e = sp209api_device_open(h,d,SP209API_VARIANT_STD);
        if (e == IHWAPI_OK)
        {
            DBG << "Device is open";
        }
        else
        {
            DBG << "Device not open! error code = " << e ;
        }

    }
    sp209api_free_device_list(h);

    if (e == IHWAPI_OK)
    {
        memset(&settings,0,sizeof (settings));
        settings.sampling_depth = 250e3;
        settings.post_trig_depth = settings.sampling_depth * 0.9;
        settings.thresh_cfg[0] = SP209API_X_TH_3V3;
        settings.thresh_cfg[1] = SP209API_X_TH_3V3;
        settings.thresh_cfg[2] = SP209API_X_TH_3V3;
        sp209api_trigger_description_t trg;
        trg.type = sp209api_trigger_type_t::SP209API_TRG_NOTRIG;
        trg.channel = 1;
        e = sp209api_launch_new_capture_simple_trigger(h,trg,settings);
        bool cfg_done = false;
        if (e == IHWAPI_OK)
        {
            while(cfg_done == false)
            {
                sp209api_get_config_done_flag(h,&cfg_done);
                msleep(200);
            }
            DBG << "Device Config done, new capture launched";
        }
        else
        {
            DBG << "Launch New capture error = " << e;

        }
    }



    if (e == IHWAPI_OK)
    {
        DBG << "Waiting for trigger..." << endl;
        bool trig_flag = false;
        while (trig_flag == false)
        {
            sp209api_get_triggered_flag(h,&trig_flag);
            msleep(200);
        }
        DBG << "Trigg'd";
        bool capt_done = false;
        while(capt_done == false)
        {
            sp209api_get_capture_done_flag(h,&capt_done);
            msleep(200);
        }

        const uint8_t ch = 1;
        sp209api_get_available_samples(h,&samples_count,&post_trig_samples);
        sp209api_trs_reset(h,ch);
        trs.sampple_index = 0;
        DBG << "Capture done, total captured samples = " << samples_count;
        bool is_not_last = true;
        while (is_not_last)
        {
            sp209api_trs_get_next(h,ch,&trs);
            DBG << "TRS @" << trs.sampple_index << "[" << int(trs.value) << "]";
            sp209api_trs_is_not_last(h,ch,&is_not_last);
        }
    }

    if (e == IHWAPI_OK)
    {
        DBG << "Closing device";
        sp209api_device_power_off(h); //All done, power off.
    }

    sp209api_free(h);
    DBG << "Done" << std::endl;
    return 0;
}
