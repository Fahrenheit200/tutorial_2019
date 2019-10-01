## Background Recovery

- Author: Kevin Shao

- Revised: Kevin Shao

- Date: 2019-09-29

- Version: 1.0.0

- Abstract: This is the readme tutorial about LinkNode program.

### Functions:
    find the backfround of a video
### Interfaces:
```C++
// Initialize the class and open the video
void Recovery::readVideo(string filePath)；
// Read the video and recover the background
void Recovery::process()；
// Show the result and write into file
void Recovery::showResult()；
```
### Depend Libraries:
```
OpenCV 3
```
### Build Guide:
```Bash
make clean
make
```
### Test:
```Bash
./bin/main ./resource/video0.mp4
```






