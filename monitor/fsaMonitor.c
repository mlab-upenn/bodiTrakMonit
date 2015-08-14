#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsa.h"

void main() {
	FSAT7 t7;
	fsat7Initialize();
	t7 = fsat7Create(0, 0);
	if (t7) {
		int c, columns = fsat7GetColumnCount(t7);
		int r, rows = fsat7GetRowCount(t7);
		float* values = malloc(columns * rows * sizeof(float));
		if (values) {
			float minimum, maximum;
			char units[32];
			if (fsat7LoadCalibration(t7)) {
				minimum = fsat7GetMinimum(t7);
				maximum = fsat7GetMaximum(t7);
				fsat7GetUnits(t7, units);
			}
			else {
				minimum = 0;
				maximum = fsat7GetConductance(t7);
				strcpy(units, "uSiemens");
			}
			printf("%dx%d  %f-%f %s\r\n", columns, rows, minimum, maximum, units);
			if (fsat7Scan(t7, values, NULL)) {
				float* value = values;
				for (r = 0; r < rows; ++r) {
					for (c = 0; c < columns; ++c, ++value) printf("%4d", (int)(*value));
					puts("");
				}
			}
			else puts("Failed to scan sensor array.");
			free(values);
		}
		else puts("Failed to allocate value buffer.");
		fsat7Destroy(t7);
	}
	else puts("Failed to connect to a sensor array.");
	fsat7Uninitialize();
}
