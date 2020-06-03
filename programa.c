#include "mbed.h"
#include "ultrasonic.h"
#include "motordriver.h"
#include "StepperMotor.h"

#ifndef MBED_STEPPERMOTOR

#define MBED_STEPPERMOTOR
#define MAX_PPS 50

void dist(int distance)
{
    //put code here to execute when the distance has changed
    printf("Distance %d mm\r\n", distance);
}

ultrasonic mu(p6, p7, .1, 1, &dist); //Set the trigger pin to p6 and the echo pin to p7
                                     //have updates every .1 seconds and a timeout after 1
                                     //second, and call dist when the distance changes

Motor A(p22, p6, p5, 1); // pwm, fwd, rev, can brake
Motor B(p21, p7, p8, 1); // pwm, fwd, rev, can brake

StepperMotor m(p21, p22, p23, p24);

BusOut myled(LED1, LED2, LED3, LED4);
Serial blue(p28, p27);

int main()
{
    m.set_sync_mode(StepperMotor::SYNCHRONOUS);
    m.set_power_ctrl(true);

    mu.startUpdates(); //start measuring the distance

    char ch;
    pc.baud(115200);
    bt.baud(115200);

    char bnum = 0;
    char bhit = 0;

    while (1)
    {
        //Do something else here
        mu.checkDistance(); //call checkDistance() as much as possible, as this is where
                            //the class checks if dist needs to be called.
        for (float s = -1.0; s < 1.0; s += 0.01)
        {
            A.speed(s);
            B.speed(s);
            wait(0.02);
        }
        A.stop();
        B.stop();
        wait(1);
        A.coast();
        B.coast();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        m.go_angle(120);
        wait(0.5);

        m.go_angle(240);
        wait(0.5);

        m.go_angle(0);
        wait(0.5);

        m.go_angle(240);
        wait(0.5);

        m.go_angle(120);
        wait(0.5);

        m.go_angle(0);
        wait(0.5);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (bt.readable())
        {
            ch = bt.getc();
            pc.printf("%c", ch);
            bt.printf("%c", ch);
        }

        else if (pc.readable())
        {
            ch = pc.getc();
            bt.printf("%c", ch);
            pc.printf("%c", ch);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (blue.getc() == '!')
        {
            if (blue.getc() == 'B')
            {                       //button data packet
                bnum = blue.getc(); //button number
                bhit = blue.getc(); //1=hit, 0=release
                if (blue.getc() == char(~('!' + 'B' + bnum + bhit)))
                {                       //checksum OK?
                    myled = bnum - '0'; //current button number will appear on LEDs
                    switch (bnum)
                    {
                    case '1': //number button 1
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    case '2': //number button 2
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    case '3': //number button 3
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    case '4': //number button 4
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    case '5': //button 5 up arrow
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    case '6': //button 6 down arrow
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    case '7': //button 7 left arrow
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    case '8': //button 8 right arrow
                        if (bhit == '1')
                        {
                            //add hit code here
                        }
                        else
                        {
                            //add release code here
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}