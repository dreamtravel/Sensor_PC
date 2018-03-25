#include "data.h"
#include <math.h>
#include "cmd/sensorprotocol.h"
#include "tool/datacalculate.h"
Sensor_Info_All sensor_info_all;
Data::Data()
{
    hall.a = hall.b = 0;
    irfs.a = irfs.b = 0;
    mcph.a = mcph.b = 0;
    mfs.x = mfs.y = mfs.z = 0;
    trac.x = trac.y = trac.z = 0;
    ircj.x=ircj.y=ircj.z=0;
    sht.a = sht.b = 0;
    gas = irds = rsir = rnsw = shk = 0;
    ilin = dip = 0;
    aipr = amp = dust= inam = ulr = the = 0;
    sensor_info_all.GAS_Info=0;
    sensor_info_all.IRDS_Info=0;
    sensor_info_all.RSIR_Info=0;
    sensor_info_all.RNSW_Info=0;
    sensor_info_all.SHK_Info=0;
    memset(sensor_info_all.HALL_Info,0,2);
    memset(sensor_info_all.IRFS_Info,0,2);
    memset(sensor_info_all.MCPH_Info,0,2);
    memset(sensor_info_all.MFS_Info,0,6);
    memset(sensor_info_all.BH1750_Info,0,2);
    memset(sensor_info_all.AIPR_Info,0,2);
    memset(sensor_info_all.TRAC_Info,0,6);
    memset(sensor_info_all.SHT_Info,0,4);
    memset(sensor_info_all.DIP_Info,0,2);
    memset(sensor_info_all.AMP_Info,0,2);
    memset(sensor_info_all.DUST_Info,0,2);
    memset(sensor_info_all.IRCJ_Info,0,3);
    memset(sensor_info_all.INAM_Info,0,3);
    memset(sensor_info_all.ULR_Info,0,3);
    memset(sensor_info_all.THE_Info,0,3);
}

void Data::dataReceive()
{
            float temp=0;
            hall.a=sensor_info_all.HALL_Info[0];
            hall.b=sensor_info_all.HALL_Info[1];
            gas =sensor_info_all.GAS_Info;
            irds = sensor_info_all.IRDS_Info;
            irfs.a=sensor_info_all.IRFS_Info[0];
            irfs.b=sensor_info_all.IRFS_Info[1];
            rsir = sensor_info_all.RSIR_Info;
            mcph.a=sensor_info_all.MCPH_Info[0];
            mcph.b=sensor_info_all.MCPH_Info[1];
            rnsw = sensor_info_all.RNSW_Info;
            shk =sensor_info_all.SHK_Info;
            mfs = DataCalculate::GetMagData(sensor_info_all.MFS_Info);
            ilin = (sensor_info_all.BH1750_Info[0]*256 + sensor_info_all.BH1750_Info[1])/1.2;
            aipr = (sensor_info_all.AIPR_Info[0]*256 + sensor_info_all.AIPR_Info[1])*2.895/1000;
            trac = DataCalculate::GetMagData(sensor_info_all.TRAC_Info);
            sht = DataCalculate::GetHumTempData(sensor_info_all.SHT_Info);
            dip = DataCalculate::ADCGetVoltage(sensor_info_all.DIP_Info);
            dip =asin(dip/2.0-0.825)*180/3.1415926535898;// asin(1/2(Vout-1/2Vdd))
            amp = sensor_info_all.AMP_Info[0]*256 + sensor_info_all.AMP_Info[1];
            amp=(amp*3.3/4095.0-2.5)/0.185;
            dust = (sensor_info_all.DUST_Info[0]*256 + sensor_info_all.DUST_Info[1])*3.3/4095;
            if(dust<1)dust=0;
            else if(dust<1.5&&dust>=1) dust=0.1;
            else if(dust<2&&dust>=1.5) dust=0.2;
            else if(dust<2.5&&dust>=2) dust=0.3;
            else if(dust<3&&dust>=2.5) dust=0.4;
            else if(dust<3.5&&dust>=3) dust=0.5;
            else dust=0.6;

            ircj =DataCalculate::GetReadData(sensor_info_all.IRCJ_Info);
            temp = (sensor_info_all.INAM_Info[0]*256 + sensor_info_all.INAM_Info[1])*3.3/4095;
            inam=5263*temp-8578;
            ulr = (sensor_info_all.ULR_Info[0]*256 + sensor_info_all.ULR_Info[1])*3300/4095.0;
            if(ulr<50) ulr=0;
            else if(ulr<227) ulr=1;
            else if(ulr<318) ulr=2;
            else if(ulr<408) ulr=3;
            else if(ulr<503) ulr=4;
            else if(ulr<606) ulr=5;
            else if(ulr<696) ulr=6;
            else if(ulr<795) ulr=7;
            else if(ulr<881) ulr=8;
            else if(ulr<976) ulr=9;
            else if(ulr<1079) ulr=10;
            else if(ulr<1170) ulr=11;
            else ulr=ulr/100;
            the =(sensor_info_all.THE_Info[0]*256 + sensor_info_all.THE_Info[1])*1023.75/4095;
}
