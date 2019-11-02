## 图像处理

-作者: 李泓舟

-修订: 李泓舟

-日期: 2019.11.2

-版本: v1.0.0

-摘要: 提取二维码



#### 接口示例

-Qrcode::Qrcode(string filePath);

-void Qrcode::show();



#### 依赖库

-include<opencv2/opencv.hpp>

-include<algorithm>





#### 编译提示

基础题

$ cd canny

$ mkdir bin && cd bin

$ cmake ..

$ make

$ ./canny <file_path>





提取二维码

$ cd Qrcode

$ mkdir bin && cd bin

$ cmake ..

$ make

$  ./Qrcode <file_path>      

 (注意：为方便起见，默认提取二维码的四张图片放在同一文件夹下且文件名均形如image_a.jpg, image_b.jpg,故此处路径是文件夹的路径，Image_processing_file\qrcode_picture\level1\Group_A）)



