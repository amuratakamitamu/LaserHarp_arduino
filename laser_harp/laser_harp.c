#include "MIDIUSB.h"

const int SW1 = 2;

const int sensor[6] = {A0, A1, A2, A3, A4, A5};
const int sensor_th = 600;

bool sensor_state_now[6] = {0, 0, 0, 0, 0, 0};
bool sensor_state_old[6] = {0, 0, 0, 0, 0, 0};

int note_no[6] = {60, 62, 64, 65, 67, 69};

void setup() {

pinMode(SW1, INPUT);
pinMode(LED_BUILTIN, OUTPUT);

}


void loop() {

for(int string=0; string<6; string++){
    if(analogRead(sensor[string]) < sensor_th){
      // ON
    sensor_state_now[string] = 1;
    }
    else {
      // OFF
    sensor_state_now[string] = 0; 
    }
}

for(int string=0; string<6; string++){
    if(sensor_state_now[string] != sensor_state_old[string]){
      noteOn(0, note_no[string], 64 * sensor_state_now[string]);
    MidiUSB.flush();
    }
    sensor_state_old[string] = sensor_state_now[string];
}

}

void noteOn(byte channel, byte pitch, byte velocity) {
midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
MidiUSB.sendMIDI(noteOff);
}
