#include "ADS1256.h"

//ADS1256(int DRDY_pin, int RESET_pin, int SYNC_pin, int CS_pin, int MISO_pin, int CLK_pin, int MOSI_pin, float VREF)
ADS1256 ADC(ADC_DRDY, ADC_RST, ADC_SYNC, ADC_CS, MISO, SCLK, MOSI, 2.500);  //DRDY, RESET, SYNC(PDWN), CS, MISO, CLK, MOSI, VREF(float).

long rawConversion = 0;  //24-bit raw value
float voltageValue = 0;  //human-readable floating point value

int singleEndedChannels[8] = { SING_0, SING_1, SING_2, SING_3, SING_4, SING_5, SING_6, SING_7 };  //Array to store the single-ended channels
int differentialChannels[4] = { DIFF_0_1, DIFF_2_3, DIFF_4_5, DIFF_6_7 };                         //Array to store the differential channels
int inputChannel = 0;                                                                             //Number used to pick the channel from the above two arrays
char inputMode = ' ';                                                                             //can be 's' and 'd': single-ended and differential

int pgaValues[7] = { PGA_1, PGA_2, PGA_4, PGA_8, PGA_16, PGA_32, PGA_64 };  //Array to store the PGA settings
int pgaSelection = 0;                                                       //Number used to pick the PGA value from the above array

int drateValues[16] = {
  DRATE_30000SPS,
  DRATE_15000SPS,
  DRATE_7500SPS,
  DRATE_3750SPS,
  DRATE_2000SPS,
  DRATE_1000SPS,
  DRATE_500SPS,
  DRATE_100SPS,
  DRATE_60SPS,
  DRATE_50SPS,
  DRATE_30SPS,
  DRATE_25SPS,
  DRATE_15SPS,
  DRATE_10SPS,
  DRATE_5SPS,
  DRATE_2SPS
};  //Array to store the sampling rates

int drateSelection = 0;  //Number used to pick the sampling rate from the above array

String registers[11] = {
  "STATUS",
  "MUX",
  "ADCON",
  "DRATE",
  "IO",
  "OFC0",
  "OFC1",
  "OFC2",
  "FSC0",
  "FSC1",
  "FSC2"
};  //Array to store the registers

int registerToRead = 0;        //Register number to be read
int registerToWrite = 0;       //Register number to be written
int registerValueToWrite = 0;  //Value to be written in the selected register


ADC.InitializeADC();  //See the documentation for every details
//Setting up CS, RESET, SYNC and SPI
//Assigning default values to: STATUS, MUX, ADCON, DRATE
//Performing a SYSCAL


ADC.setPGA(PGA_1);

ADC.setMUX(DIFF_6_7);

ADC.setDRATE(DRATE_5SPS);

ADC.readRegister(IO_REG);

ADC.readRegister(MUX_REG);

ADC.readRegister(DRATE_REG);

ADC.stopConversion();  //stop continuous conv.

ADC.sendDirectCommand(SELFCAL);  //selfcal command

ADC.convertToVoltage(ADC.readSingleContinuous());  //read single channel continuously

ADC.convertToVoltage(ADC.cycleSingle());  //cycle single ch reading

ADC.convertToVoltage(ADC.cycleDifferential());  //cycle diff ch reading

ADC.readSingle();  //read the selected ch for once

ADC.setMUX(singleEndedChannels[inputChannel]);
//SING_0, SING_1, SING_2, SING_3, SING_4, SING_5, SING_6, SING_7

ADC.setMUX(differentialChannels[inputChannel]);
//DIFF_0_1, DIFF_2_3, DIFF_4_5, DIFF_6_7

ADC.setPGA(pgaValues[pgaSelection]);
//PGA_1, PGA_2, PGA_4, PGA_8, PGA_16, PGA_32, PGA_64

ADC.setDRATE(drateValues[drateSelection]);
//DRATE_30000SPS,DRATE_15000SPS, DRATE_7500SPS, DRATE_3750SPS, DRATE_2000SPS, DRATE_1000SPS, DRATE_500SPS
//DRATE_100SPS, DRATE_60SPS, DRATE_50SPS, DRATE_30SPS, DRATE_25SPS, DRATE_15SPS, DRATE_10SPS, DRATE_5SPS, DRATE_2SPS

ADC.readRegister(registerToRead);
//"STATUS", "MUX", "ADCON", "DRATE", "IO", "OFC0", "OFC1", "OFC2", "FSC0", "FSC1", "FSC2"

ADC.writeRegister(registerToWrite, registerValueToWrite);
//Example: "W1 35" will write 35 ("00100011") on register 1 which is the MUX register.
//This will make the input as DIFF_2_3 (A2(+) & A1(-))
