# Clock

目前共有3个版本

* [Arduino-Clock](#Arduino-Clock)
* [51_12864_Clock](#51_12864_Clock)

---
# Arduino Clock
 > 基于Atmega芯片、Arduino平台的桌面时钟.  
 > 具有计时、倒计时、闹钟等功能.  
 > 支持掉电记忆,掉电走时.  

## 功能
* 查看、调整时间、闹钟. 
* 双精度的计时、倒计时.范围0-59min59s.精度10ms.
* 支持掉电记忆,掉电走时.
   > 5ppm晶振配合足够耐心，周误差能调到2s
* 精度0.1°C的温度显示.
* 自动亮度调节,环境黑暗时自动调暗.

## 硬件
* 主控芯片: 所有DIP28封装的Atmega系列均可.
   > 建议使用Atmega8/Atmega88/Atmega168/Atmega328.FLASH要求8k及以上.
* DS1302实时时钟芯片 + CR1220锂电池.
* 0.8寸共阳一位数码管x4.
* 蜂鸣器.

## 软件
* 未使用库,仅使用原生函数完成.
* 函数式编程.

---

# 51_Clock

注意 本仓库51CLK均基于**非**常见单片机  
仅提供对应代码  
![](https://pic.imgdb.cn/item/62996b8909475431292c6b8d.jpg)

## 功能
* 查看、调整时间. 
* 双精度的计时、倒计时.范围0-59min59s.精度10ms.
* 支持掉电记忆,掉电走时.
* 自动亮度调节,环境黑暗时自动调暗.

## 硬件
* 主控芯片: 中基国威F05S16.
* DS1302实时时钟芯片 + CR1220锂电池.
* 0.8寸时钟专用数码管.

## 软件
* 使用原生函数完成.
* 函数式编程.

# 51_12864_Clock

![](https://pic.imgdb.cn/item/62996c6709475431292d4682.jpg)

![](https://pic.imgdb.cn/item/62996c6709475431292d466a.jpg)

![](https://pic.imgdb.cn/item/62996c6709475431292d4670.jpg)

## 功能
* 查看、调整时间、日期.
* 支持掉电记忆,掉电走时.
* 自动显示当日课表.
* 高考倒计时.
* 可调背光.
 > 字体已经调整为更美观的字体.

## 硬件
* 主控芯片: 中基国威F05S16.
* DS1302实时时钟芯片 + 备用电容.
* 12864带背光屏幕.

![](https://pic.imgdb.cn/item/62996c6709475431292d4678.jpg)

## 软件
* 未使用库,使用原生IO完成.
* 函数式编程.

