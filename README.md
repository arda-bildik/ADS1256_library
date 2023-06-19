# ADS1256_library
RPi Pico library for Texas Instruments ADS1256 24-bit ADC

This library is a modified version of Curious Scientist's ADS1256 library to work with RP2040 based boards.
Original library of Curious Scientist's ADS1256 library can be found here:
https://curiousscientist.tech/ads1256-custom-library

Also please refer to the Texas Instruments ADS1256 datasheet for more detailed explanation on the commands and registers.
https://www.ti.com/lit/ds/symlink/ads1256.pdf?ts=1687193761750

# Library Functions

ADS1256 ADC(ADC_DRDY, ADC_RST, ADC_SYNC, ADC_CS, MISO, SCLK, MOSI, Vref);

ADC.InitializeADC();

ADC.setPGA(PGA_MODE);
PGA_MODE -> PGA_1, PGA_2, PGA_4, PGA_8, PGA_16, PGA_32, PGA_64


ADC.setMUX(MUX_MODE);
MUX_MODE for Single Ended -> SING_0, SING_1, SING_2, SING_3, SING_4, SING_5, SING_6, SING_7
MUX_MODE for Differentia -> l DIFF_0_1, DIFF_2_3, DIFF_4_5, DIFF_6_7


ADC.setDRATE(DRATE_MODE);
DRATE_MODE values:
DRATE_30000SPS,  DRATE_15000SPS,  DRATE_7500SPS,  DRATE_3750SPS,  DRATE_2000SPS,
DRATE_1000SPS,  DRATE_500SPS,  DRATE_100SPS,  DRATE_60SPS,  DRATE_50SPS, 
DRATE_30SPS,  DRATE_25SPS, DRATE_15SPS,  DRATE_10SPS,  DRATE_5SPS,  DRATE_2SPS


ADC.readRegister(REGISTER_NAME);
REGISTER_NAME values:
  STATUS - Status register that contains ADC config
  MUX    - Input Multiplexer Control Register
  ADCON  - Clock/Sensor Detect/PGA Setting Register
  DRATE  - ADC Data Rate Register
  IO     - GPIO Control Register
  OFC0   - Offset Calibration Byte 0
  OFC1   - Offset Calibration Byte 1
  OFC2   - Offset Calibration Byte 2
  FSC0   - Full-scale Calibration Byte 0
  FSC1   - Full-scale Calibration Byte 1
  FSC2   - Full-scale Calibration Byte 2


ADC.writeRegister(REGISTER_NAME, DATA_TO_BE_WRITTEN);
  Example: "("MUX","35"); will write 35 ("00100011") on the MUX register.
  This will make the input set as DIFF_2_3 (A2(+) & A1(-))
  Refer to datasheet for values for registers<


ADC.stopConversion();


ADC.sendDirectCommand(COMMAND);
COMMAND values:
  WAKEUP   - Completes SYNC and Exits Standby Mode
  RDATA    - Read Data
  RDATAC   - Read Data Continuously
  SDATAC   - Stop Read Data Continuously
  RREG     - Read from REG rrr
  WREG     - Write to REG rrr
  SELFCAL  - Offset and Gain Self-Calibration
  SELFOCAL - Offset Self-Calibration
  SELFGCAL - Gain Self-Calibration
  SYSOCAL  - System Offset Calibration
  SYSGCAL  - System Gain Calibration
  SYNC     - Synchronize the A/D Conversion
  STANDBY  - Begin Standby Mode
  RESET    - Reset to Power-Up Values

ADC.readSingleContinuous();  //Continuously read raw data from the connected channel

ADC.cycleSingle();  //Cycle single channel reading

ADC.cycleDifferential();  //Cycle differential channel reading

ADC.readSingle();  //Read the raw data from selected channel

ADC.convertToVoltage(RAW_ADC_DATA);  //Convert the given raw data to voltage

ADC.setBuffer(BUFFER); //Input Buffer false(default)/true

ADC.setAutoCal(ACAL); //Automatic System Calibration false(default)/true
