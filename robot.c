//LED not implemented

#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

DigitalOut fingerMotorEnablePin(p16);
DigitalOut fingerMotorPin1(p17);
DigitalOut fingerMotorPin2(p18);
DigitalOut wristMotorEnablePin(p19);
DigitalOut wristMotorPin1(p20);
DigitalOut wristMotorPin2(p21);
DigitalOut elbowMotorEnablePin(p22);
DigitalOut elbowMotorPin1(p23);
DigitalOut elbowMotorPin2(p24);
DigitalOut shoulderMotorEnablePin(p25);
DigitalOut shoulderMotorPin1(p26);
DigitalOut shoulderMotorPin2(p27);
DigitalOut baseMotorEnablePin(p28);
DigitalOut baseMotorPin1(p29);
DigitalOut baseMotorPin2(p30);


Serial device(p13, p14);  // tx, rx
Serial pc(USBTX, USBRX); // tx, rx

int main()
{
    char rchar=0;
//wake up device - needs more work and a timeout
    device.putc('b');
    while (device.getc()!='o') {
        device.putc('b');
        wait(0.2);
    }
    baseMotorEnablePin      = 1;
    shoulderMotorEnablePin  = 1;
    elbowMotorEnablePin     = 1;
    wristMotorEnablePin     = 1;
    fingerMotorEnablePin    = 1;
start:
    while (1) {
        device.putc('d'); //SD Recognition - 'd' goes with 'r'
        device.putc('B'); //Use group 1
        //Use SD
        while (device.readable()!=0) {}
        if (device.getc()=='r') {
            device.putc(' ');
            rchar=device.getc();
            pc.putc(rchar);
            pc.putc('0');
            led1=!led1;
            if (rchar=='A') {//bumblebee
                //do something fun to start
                fingerMotorPin1=1;
                fingerMotorPin2=0;
                wait(1);
                fingerMotorPin1=0;
                fingerMotorPin2=0;
                wait(1);
                baseMotorPin1 = 1;
                baseMotorPin2 = 0;
                wait(1);
                baseMotorPin1 = 0;
                baseMotorPin2 = 0;
            } else if (rchar=='B') { //finger
                wait(0.2);
                device.putc('i'); //SI Recognition 'i' goes with 's'
                device.putc('B'); //Use Wordset 1
                while (device.readable()!=0) {}
                if (device.getc()=='s') {
                    device.putc(' ');
                    rchar=device.getc();
                    led2=!led2;
                    pc.putc(rchar);
                    pc.putc('1');
                    if (rchar=='C') {//turn
                        wait(0.2);
                        device.putc('d'); //SI Recognition
                        device.putc('C'); //Use Wordset 2
                        while (device.readable()!=0) {}
                        if (device.getc()=='r') {
                            device.putc(' ');
                            rchar=device.getc();
                            led3=!led3;
                            pc.putc(rchar);
                            pc.putc('2');
                            if (rchar=='A') {//open
                                fingerMotorPin1=1;
                                fingerMotorPin2=0;
                            } else if (rchar=='B') { //close
                                fingerMotorPin1=0;
                                fingerMotorPin2=1;
                            } else
                                goto start;
                        }
                    } else if (rchar=='G') { //stop
                        fingerMotorPin1=0;
                        fingerMotorPin2=0;
                    } else
                        goto start;
                } else { //stop
                    fingerMotorPin1=0;
                    fingerMotorPin2=0;
                    goto start;
                }
            } else if (rchar=='C') { //wrist
                wait(0.2);
                device.putc('i'); //SI Recognition
                device.putc('B'); //Use Wordset 1
                while (device.readable()!=0) {}
                if (device.getc()=='s') {
                    device.putc(' ');
                    rchar=device.getc();
                    led2=!led2;
                    pc.putc(rchar);
                    pc.putc('1');
                    if (rchar=='B') {//move
                        wait(0.2);
                        device.putc('i'); //SI Recognition
                        device.putc('C'); //Use Wordset 2
                        while (device.readable()!=0) {}
                        if (device.getc()=='s') {
                            device.putc(' ');
                            rchar=device.getc();
                            led3=!led3;
                            pc.putc(rchar);
                            pc.putc('2');
                            if (rchar=='C') {//up
                                wristMotorPin1=1;
                                wristMotorPin2=0;
                            } else if (rchar=='D') { //down
                                wristMotorPin1=0;
                                wristMotorPin2=1;
                            } else
                                goto start;
                        }
                    } else if (rchar=='G') { //stop
                        wristMotorPin1=0;
                        wristMotorPin2=0;
                    } else
                        goto start;
                } else { //stop
                    wristMotorPin1=0;
                    wristMotorPin2=0;
                    goto start;
                }
            } else if (rchar=='D') { //elbow
                wait(0.2);
                device.putc('i'); //SI Recognition
                device.putc('B'); //Use Wordset 1
                while (device.readable()!=0) {}
                if (device.getc()=='s') {
                    device.putc(' ');
                    rchar=device.getc();
                    led2=!led2;
                    pc.putc(rchar);
                    pc.putc('1');
                    if (rchar=='B') {//move
                        wait(0.2);
                        device.putc('i'); //SI Recognition
                        device.putc('C'); //Use Wordset 2
                        while (device.readable()!=0) {}
                        if (device.getc()=='s') {
                            device.putc(' ');
                            rchar=device.getc();
                            led3=!led3;
                            pc.putc(rchar);
                            pc.putc('2');
                            if (rchar=='C') {//up
                                elbowMotorPin1=1;
                                elbowMotorPin2=0;
                            } else if (rchar=='D') { //down
                                elbowMotorPin1=0;
                                elbowMotorPin2=1;
                            } else
                                goto start;
                        }
                    } else if (rchar=='G') { //stop
                        elbowMotorPin1=0;
                        elbowMotorPin2=0;
                    } else
                        goto start;
                } else { //stop
                    elbowMotorPin1=0;
                    elbowMotorPin2=0;
                    goto start;
                }
            } else if (rchar=='E') { //shoulder
                wait(0.2);
                device.putc('i'); //SI Recognition
                device.putc('B'); //Use Wordset 1
                while (device.readable()!=0) {}
                if (device.getc()=='s') {
                    device.putc(' ');
                    rchar=device.getc();
                    led2=!led2;
                    pc.putc(rchar);
                    pc.putc('1');
                    if (rchar=='B') {//move
                        wait(0.2);
                        device.putc('i'); //SI Recognition
                        device.putc('C'); //Use Wordset 2
                        while (device.readable()!=0) {}
                        if (device.getc()=='s') {
                            device.putc(' ');
                            rchar=device.getc();
                            led3=!led3;
                            pc.putc(rchar);
                            pc.putc('2');
                            if (rchar=='E') {//forward
                                shoulderMotorPin1=1;
                                shoulderMotorPin2=0;
                            } else if (rchar=='F') { //backward
                                shoulderMotorPin1=0;
                                shoulderMotorPin2=1;
                            } else
                                goto start;
                        }
                    } else if (rchar=='G') { //stop
                        shoulderMotorPin1=0;
                        shoulderMotorPin2=0;
                    } else
                        goto start;
                } else { //stop
                    shoulderMotorPin1=0;
                    shoulderMotorPin2=0;
                    goto start;
                }
            } else if (rchar=='F') { //base
                wait(0.2);
                device.putc('i'); //SI Recognition
                device.putc('B'); //Use Wordset 1
                while (device.readable()!=0) {}
                if (device.getc()=='s') {
                    device.putc(' ');
                    rchar=device.getc();
                    led2=!led2;
                    pc.putc(rchar);
                    pc.putc('1');
                    if (rchar=='C') {//turn
                        wait(0.2);
                        device.putc('i'); //SI Recognition
                        device.putc('C'); //Use Wordset 2
                        while (device.readable()!=0) {}
                        if (device.getc()=='s') {
                            device.putc(' ');
                            rchar=device.getc();
                            led3=!led3;
                            pc.putc(rchar);
                            pc.putc('2');
                            if (rchar=='A') {//left
                                baseMotorPin1=1;
                                baseMotorPin2=0;
                            } else if (rchar=='B') { //right
                                baseMotorPin1=0;
                                baseMotorPin2=1;
                            } else
                                goto start;
                        }
                    } else if (rchar=='G') { //stop
                        baseMotorPin1=0;
                        baseMotorPin2=0;
                    } else
                        goto start;
                } else { //stop
                    baseMotorPin1=0;
                    baseMotorPin2=0;
                    goto start;
                }
            } else if (rchar=='G') { //light
                wait(0.2);
                device.putc('d'); //SD Recognition
                device.putc('C'); //group 2
                while (device.readable()!=0) {}
                if (device.getc()=='r') {
                    device.putc(' ');
                    rchar=device.getc();
                    led2=!led2;
                    pc.putc(rchar);
                    pc.putc('1');
                    if (rchar=='C') {//on
                    } else if (rchar=='D') { //off
                    } else
                        goto start;
                } else
                    goto start;
            } else { //estop
                baseMotorPin1=0;
                baseMotorPin2=0;
                pc.putc(' ');
                shoulderMotorPin1=0;
                shoulderMotorPin2=0;
                pc.putc(' ');
                fingerMotorPin1=0;
                fingerMotorPin2=0;
                pc.putc(' ');
                wristMotorPin1=0;
                wristMotorPin2=0;
                pc.putc(' ');
                elbowMotorPin1=0;
                elbowMotorPin2=0;
                pc.putc(' ');
            }
        }
    }
}