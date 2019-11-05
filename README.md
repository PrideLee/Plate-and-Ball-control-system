# Plate-and-Ball control system

- Based on steering engine control technology, PID (proportional plus integral plus derivative) control algorithm, images processing technology and single chip development, we design and achieve a plate-and-ball control system, which collects the ball position and motion information by a camera, as actuator, linkage mechanism driven by steering engine controls tilts the plate, then controling the ball to finish specific motion.
- Hardwares include camera stant, SCM development board, steering engine, OV7670 camera, linkage, keyboard and DC power supply.
- The system adopts PID control of a single loop strategy, camera collects the real position information and calculating the position deviation. Based on the deviation, we utilize PID algorithm to get the duty cycle of PWM, through this singnal to drive the steering engine, thus we can control the tilt of plate to plan the motion track of the ball.

## 摘要

本滚球系统以STM32F4单片机为核心，舵机作为执行机构，通过连杆机构使平板倾斜控制小球完成指定运动。结合舵机控制技术，PID控制算法，图形图像处理技术。硬件部分由支架、舵机、连杆、OV7670摄像头、键盘、直流电源、单片机等组成。系统采用单环PD控制，由摄像读取平板小球灰度图并转化为二值图，得到小球在平板上的坐标。舵机控制采用PWM占空比调制，由PD算法得到占空比，控制舵机转过一定角度以使平板倾斜，使小球完成各种动作。测试各项指标都符合要求。
