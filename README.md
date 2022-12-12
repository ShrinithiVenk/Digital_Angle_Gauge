# PES_Final_Project DIGITAL ANGLE GAUGE
## BRIEF:
     Author: Shrinithi Venkatesan
     MAIL: shve4446@colorado.edu
   
## DIGITAL ANGLE GAUGE:
A digital angle gauge measures and determines the angle of a given object. This application uses the inbuilt accelerometer MMA8451Q embedded on the FRDM KL25Z. The MMA8415Q is a 3 axis, low power, 14 bit resolution sensor, which ensures accurate results. The gauge references respective angles from the pre-calibrated 0 degrees.The GPIOs and the User Interface are configured to display the real time outputs of the gauge.

## FUNCTIONALITY:
Through the UI terminal , the user will provide the angle needed to be measured and the LEDs will blink gradually through attaining the respective angle. When the user clicks the calibrate <angle>, the interrupt will be generated to calibrate the desired angle as a zero degree reference. The real time measured angles and the current process information is fed to the user interface terminal.
  
###Commands:
                      Author            : Generates the author name.
                      Angle<angle>      : Measures the desired angle requested by the user. 
                      Calibrate<angle>  : Sets the desired angle as a Zero degree reference.
                      Help              : Reprints the command menu.
                      Reset             : Resets the angle to reference zero.
  
 
### Source Files included:
  
                  cbfifo.c
                  accel.c
                  uart.c
                  i2c.c
                  Digital_Angle_Gauge.c (main)
                  test_led.c
                  test_accel.c
                  test_cbfifo.c
                  systick.c
                  led.c
                  cmd.c
  
  
  ### Technologies included:
              Circular buffers - Enables UART transmission and reception.

              GPIO lines - Configure the LEDs to visual display the angles attained. 

              Interrupts - Calibrate the accelerometer to zero degrees before angle measurement and to reset  to measuring the next angle.
 
              I2C - Enable the communication of the inbuilt accelerometer MMA8514Q.

              UART - To enable communication between the command processor and the FRDM KL25Z that allows transmission and reception of data to and from the user.

              Command Processing - A user interface that gets the inputs from the user and displays live functionality of the program as showing the measured angle and               the current state of the program. 

              PWM - Tunes the LED brightness according to the measured angle.
  
  ### Hardware used:
  
           FRDM KL25Z
           MMA8451Q Accelerometer
           LED

# vedio demo link

 https://photos.app.goo.gl/1DPU6Mwrp7s5CKxu5
  


