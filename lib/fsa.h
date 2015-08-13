#ifndef FSA_H
#define FSA_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* FSAT7ID;
typedef void* FSAT7;

#define FILTER_ADC_MAXED_OUT      1
#define FILTER_CLIPPED_TOP        2
#define FILTER_CLIPPED_BOTTOM     4
#define FILTER_CORRECTED_OUTLIER  8
#define FILTER_SENSOR_DISABLED   16

int fsat7Initialize();
void fsat7Uninitialize();

FSAT7ID* fsat7CreateList();
void fsat7DestroyList(FSAT7ID* list);

FSAT7 fsat7Create(FSAT7ID t7id, int loadCal);
void fsat7Destroy(FSAT7 t7);

int fsat7GetSerialNumber(FSAT7 t7, char* serialNumber);
int fsat7GetColumnCount(FSAT7 t7);
int fsat7GetRowCount(FSAT7 t7);
float fsat7GetMinimum(FSAT7 t7);
float fsat7GetMaximum(FSAT7 t7);
int fsat7GetUnits(FSAT7 t7, char* units);
float fsat7GetConductance(FSAT7 t7);
int fsat7GetWidth(FSAT7 t7);
int fsat7GetHeight(FSAT7 t7);
int fsat7GetCalibrationDate(FSAT7 t7);
int fsat7GetCalibrationTime(FSAT7 t7);
int fsat7SetConductance(FSAT7 t7, float conductance);
int fsat7Reconnect(FSAT7 t7);
int fsat7Scan(FSAT7 t7, float* values, int* flags);
int fsat7LoadCalibration(FSAT7 t7);
int fsat7UnloadCalibration(FSAT7 t7);

typedef void* FSAAC;

FSAAC fsaacCreate(int uncalibrated);
void fsaacDestroy(FSAAC ac);
int fsaacGetPressure(FSAAC ac);
int fsaacInflate(FSAAC ac);
int fsaacDeflate(FSAAC ac);
int fsaacHold(FSAAC ac);

#ifdef __cplusplus
}
#endif

#endif

