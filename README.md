#BodiTrak Monitoring Interface
Note: Current shared library meant to be used on Linux 32-bit OS
##fsaMonitor

###Dependencies:
```
sudo apt-get install libusb-1.0 libbluetooth-dev bluetooth
```
###Build:
```
cd monitor
make
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
- Add header information to output file
- .m file to read txt file into matlab
- (optional) output file as .mat file for reading into Matlab


*Based on T7 SDK Version 1.0.006* 
