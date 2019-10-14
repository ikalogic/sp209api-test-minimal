#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include "sp209api.h"

#define msleep(x) //std::this_thread::sleep_for(std::chrono::milliseconds(x));

#define DEBUG_ENABLE (1)
#if DEBUG_ENABLE
    #define DBG   std::cout << endl << " "
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
    sp209api_transition_t data_trs[50];
    int devices_count = 0;
    uint32_t transitions_count = 0;




    h = sp209api_create_new_handle();
    sp209api_create_device_list(h);

    devices_count = sp209api_get_devices_count(h);
    DBG << "Found " << devices_count << " devices" ;
    if (devices_count > 0)
    {
        d = sp209api_get_device_descriptor(h,0);
        DBG << "New device, serial number = " << d.sn << ", description = " << d.desc ;
        e = sp209api_device_open(h,d,SP209API_VARIANT_STD);
        if (e == IHWAPI_OK)
        {
            DBG << "Device is open" << endl;
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
        settings.sampling_depth = 100e3;
        settings.post_trig_depth = 100e3;
        settings.thresh_cfg[0] = SP209API_X_TH_3V3;
        settings.thresh_cfg[1] = SP209API_X_TH_3V3;
        settings.thresh_cfg[2] = SP209API_X_TH_3V3;
        sp209api_trigger_description_t trg;
        trg.type = SP209API_TRG_RISING;
        trg.channel = 0;
        e = sp209api_launch_new_capture_simple_trigger(h,trg,settings);
        if (e == IHWAPI_OK)
        {
            while(sp209api_get_config_done_flag(h) == false)
            {
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
        while (sp209api_get_triggered_flag(h) == false)
        {
            msleep(200);
        }
        DBG << "Trigg'd";
        while(sp209api_get_capture_done_flag(h) == false)
        {
            msleep(200);
        }
        transitions_count = sp209api_get_available_transitions(h);
        DBG << "Capture done, transitions count = " << transitions_count;
        for (int t = 0; t < int(transitions_count-50); t+= 50)
        {
            sp209api_get_transitions(h,data_trs,50); //Get 50 transitions
            if (data_trs[49].trigger_flag)
            {
                for (int i = 0; i < 10; i++)
                {
                   DBG << data_trs[i].data_word << "\t" << int(data_trs[i].delta_samples) << "\t" << data_trs[i].trigger_flag;
                }
            }
        }
    }

    if (e == IHWAPI_OK)
    {
        DBG << "Closing device";
        sp209api_device_power_off(h); //All done, power off.
    }

    sp209api_free(h);
    return 0;
}
