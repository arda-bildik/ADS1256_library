//ADS1256 header file
/*
 Name:		ADS1256.h
 Created:	2022/07/14
 Author:	Curious Scientist
 Editor:	Notepad++
 Comment: Visit https://curiousscientist.tech/blog/ADS1256-custom-library
*/

#ifndef _ADS1256_h
#define _ADS1256_h

//Differential inputs
#define DIFF_0_1 0b00000001  //A0 + A1 as differential input
#define DIFF_2_3 0b00100011  //A2 + A3 as differential input
#define DIFF_4_5 0b01000101  //A4 + A5 as differential input
#define DIFF_6_7 0b01100111  //A6 + A7 as differential input

//Single-ended inputs
#define SING_0 0b00001111  //A0 + GND (common) as single-ended input
#define SING_1 0b00011111  //A1 + GND (common) as single-ended input
#define SING_2 0b00101111  //A2 + GND (common) as single-ended input
#define SING_3 0b00111111  //A3 + GND (common) as single-ended input
#define SING_4 0b01001111  //A4 + GND (common) as single-ended input
#define SING_5 0b01011111  //A5 + GND (common) as single-ended input
#define SING_6 0b01101111  //A6 + GND (common) as single-ended input
#define SING_7 0b01111111  //A7 + GND (common) as single-ended input

//PGA settings
#define PGA_1 0b00000000   //± 5 V
#define PGA_2 0b00000001   // ± 2.5 ±
#define PGA_4 0b00000010   //± 1.25 ±
#define PGA_8 0b00000011   //± 625 mV
#define PGA_16 0b00000100  //± 312.5 mV
#define PGA_32 0b00000101  //+ 156.25 mV
#define PGA_64 0b00000110  // ± 78.125 mV

//Datarate
#define DRATE_30000SPS 0b11110000
#define DRATE_15000SPS 0b11100000
#define DRATE_7500SPS 0b11010000
#define DRATE_3750SPS 0b11000000
#define DRATE_2000SPS 0b10110000
#define DRATE_1000SPS 0b10100001
#define DRATE_500SPS 0b10010010
#define DRATE_100SPS 0b10000010
#define DRATE_60SPS 0b01110010
#define DRATE_50SPS 0b01100011
#define DRATE_30SPS 0b01010011
#define DRATE_25SPS 0b01000011
#define DRATE_15SPS 0b00110011
#define DRATE_10SPS 0b00100011
#define DRATE_5SPS 0b00010011
#define DRATE_2SPS 0b00000011

//Status register
#define BITORDER_MSB 0
#define BITORDER_LSB 1
#define ACAL_DISABLED 0
#define ACAL_ENABLED 1
#define BUFFER_DISABLED 0
#define BUFFER_ENABLED 1

//Register addresses
#define STATUS_REG 0x00
#define MUX_REG 0x01
#define ADCON_REG 0x02
#define DRATE_REG 0x03
#define IO_REG 0x04
#define OFC0_REG 0x05
#define OFC1_REG 0x06
#define OFC2_REG 0x07
#define FSC0_REG 0x08
#define FSC1_REG 0x09
#define FSC2_REG 0x0A

//Command definitions
#define WAKEUP 0b00000000
#define RDATA 0b00000001
#define RDATAC 0b00000011
#define SDATAC 0b00001111
#define RREG 0b00010000
#define WREG 0b01010000
#define SELFCAL 0b11110000
#define SELFOCAL 0b11110001
#define SELFGCAL 0b11110010
#define SYSOCAL 0b11110011
#define SYSGCAL 0b11110100
#define SYNC 0b11111100
#define STANDBY 0b11111101
#define RESET 0b11111110
//----------------------------------------------------------------

class ADS1256 {

public:

  int DRDY_pin;
  int RESET_pin;
  int SYNC_pin;
  int CS_pin;
  int MISO_pin;
  int CLK_pin;
  int MOSI_pin;

  //Constructor
  ADS1256(int DRDY_pin, int RESET_pin, int SYNC_pin, int CS_pin, int MISO_pin, int CLK_pin, int MOSI_pin, float VREF);

  //Initializing function
  void InitializeADC();
  //ADS1256(int drate, int pga, int byteOrder, bool bufen);

  //Read a register
  long readRegister(uint8_t registerAddress);

  //Write a register
  void writeRegister(uint8_t registerAddress, uint8_t registerValueToWrite);

  //Individual methods
  void setDRATE(int drate);
  void setPGA(int pga);
  void setMUX(int mux);
  void setByteOrder(int byteOrder);
  void setBuffer(int bufen);
  void setAutoCal(int acal);
  void setGPIO(int dir0, int dir1, int dir2, int dir3);
  void writeGPIO(int dir0value, int dir1value, int dir2value, int dir3value);
  int readGPIO(int gpioPin);
  void setCLKOUT(int clkout);
  void setSDCS(int sdcs);
  void sendDirectCommand(uint8_t directCommand);

  //Get a single conversion
  long readSingle();

  //Single input continuous reading
  long readSingleContinuous();

  void readBurst(unsigned long numberOfSamples);

  //Cycling through the single-ended inputs
  long cycleSingle();  //Ax + COM

  //Cycling through the differential inputs
  long cycleDifferential();  //Ax + Ay

  //Converts the reading into a voltage value
  float convertToVoltage(int32_t rawData);

  void testAcquisitionRate(int drate, long packetSize);

  //Stop AD
  void stopConversion();



private:
  float _VREF;  //Value of the reference voltage
  //Pins
  int _DRDY_pin;   //Pin assigned for DRDY
  int _RESET_pin;  //Pin assigned for RESET
  int _SYNC_pin;   //Pin assigned for SYNC
  int _CS_pin;     //Pin assigned for CS
  int _MISO_pin;   //Pin assigned for MISO
  int _CLK_pin;    //Pin assigned for CLK
  int _MOSI_pin;   //Pin assigned for MOSI

  //Register-related variables
  int _registerAddress;       //Value holding the address of the register we want to manipulate
  int _registerValueToWrite;  //Value to be written on a selected register
  int _registerValuetoRead;   //Value read from the selected register

  //Register values
  byte _DRATE;      //Value of the DRATE register
  byte _ADCON;      //Value of the ADCON register
  byte _MUX;        //Value of the MUX register
  byte _PGA;        //Value of the PGA (within ADCON)
  byte _GPIO;       //Value of the GPIO register
  byte _STATUS;     //Value of the status register
  byte _GPIOvalue;  //GPIO value
  byte _ByteOrder;  //Byte order

  unsigned long _numberOfSamples;
  byte _outputBuffer[3];       //3-byte (24-bit) buffer for the fast acquisition - Single-channel, continuous
  long _outputValue;           //Combined value of the _outputBuffer[3]
  bool _isAcquisitionRunning;  //bool that keeps track of the acquisition (running or not)
  int _cycle;                  //Tracks the cycles as the MUX is cycling through the input channels
};




#endif
