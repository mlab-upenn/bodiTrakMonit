#BodiTrak Monitoring Interface
Note: Current Linux library compiled for Linux 32-bit OS
##example
Example program provided with SDK
##fsaMonitor
Monitoring interface program for FSA
###Dependencies:
```
sudo apt-get install libusb-1.0 libbluetooth-dev bluetooth
```
###Build:
```
cd monitor
make all
```
###Cleanup:
Please remember to run make clean before commit
```
cd monitor
make clean
```
###Usage:
After connecting BodiTrak FSA
```
sudo ./fsaMonitor outputFilename
```
output will be saved in 'rawdata/outputFilename.txt' and 'path/to/dropbox/bodiTrakMonitorRawdata/outputFilename.txt'
##TODO
- Add non-blocking IO for ease of running experiments
- Generating filenames based on date, subject, pose, trial
- Generating timestamps for captured frame
- Collecting samples at desired interval
- Add header information to output file
- .m file to read txt file into matlab
- Modify Makefile and add configuration script
.. +Purpose is to modify pathnames (esp. Dropbox path) and manage dependencies according to user setup
- (optional) output file as .mat file for reading into Matlab


*Based on T7 SDK Version 1.0.006* 
