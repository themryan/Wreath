/*
 *  Wreath.cpp
 *
 *
 *  Created by Michael Ryan on 11/11/10.
 *  Copyright 2010 Griffin Enterprise. All rights reserved.
 *
 */
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
#include "music.h"

SoftwareSerial mySerial(2, 3); // RX, TX

byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic inidicator
int  instrument = 0;

// notes A, B, C, D, E, F, G

// mapping to 24 pins
// AA to 0
// A to 8
// a to 16

//extern const int mapping[2][];
extern const char * const carol_of_bells[];
extern const char * const god_rest_ye_merry_gentlemen[];
extern const char * const jingle_bells[];
extern const char * const nutcracker_march[];
extern const int speeds[];
extern const int mappings;

const int no_of_pins = SILENT_PIN + 1;

const unsigned char pwmMap[] = { 0xFF, 0xFF, 0xFE, 0xFA, 0xDA, 0x5A, 0x58, 0x18, 0x08, 0x00, 0x00 };
 
  
 const int pwmCounts = 0x40;

int pwmThrottle = 0xFF;

//const int pwmMapLen = sizeof(pwmMap) / (2*sizeof(unsigned char));
const int pwmMapLen = sizeof(pwmMap) / (sizeof(unsigned char));

struct Tempo {
  int quarter_note;
  int thirtyTwo_note;
  int smallest_note;
  int pwmTime;
  int ftime_factor;
} ;

Tempo tempo = {
  speeds[Allegro],
  tempo.quarter_note / 8,
  tempo.thirtyTwo_note,
  tempo.smallest_note / 4,
  tempo.quarter_note
};

int pwmUnit = tempo.pwmTime / 0xFF;

const int data = 9;
const int strobe = 8;
const int clkout = 10;
const int oe = 11;
int count = 0;
int dato = 0;

int guess(int in) {
  int start = in - 'A';
  if ( in == 'S' ) {
    start = mappings - 1;
  }
  else if ( in >= ('a' + 'a') ) {
    start = (in / 2) - 'a';
  }
  else if ( in >= ('A' + 'A') ) {
    start = (in / 2) - 'A';
  }
  else if ( in >= 'a' ) {
    start = in - 'a';
  }
  if ( start < 0 ) {
    start = 0;
  }

  start *= 3;

  if ( start > mappings ) start = 0;

  return start;
}

int hashPin(int hash) {
  int index = guess(hash);
  //Serial.print("Hash: ");
  //Serial.println(hash, DEC);
  //Serial.print("Index: ");
  //Serial.println(index, DEC);
  while (mapping[index][0] != hash && index < mappings) {
    //Serial.print("Find: ");
    //Serial.println(mapping[index][0], DEC);
    index++;
  }
  if ( index != 33 && index >= mappings ) {
    index = -1;
  }

  return mapping[index][1];
}

class PMPtr {
public:
  PMPtr() : ptr(NULL) {}
  PMPtr(const char ** inPtr) : ptr(inPtr) {}
  
  PMPtr& operator ++() {
    ptr++; 
    return *this;
  }
  
  PMPtr& operator +=(int offset) {
    this->ptr = this->ptr+offset;
    return *this;
  }
  
  PMPtr& operator -=(int offset) {
    this->ptr = this->ptr-offset;
    return *this;  
  }
  
  const char ** operator +(const int offset) const {
    return this->ptr + offset;
  }
  
  const char ** operator -(const int offset) const {
    return this->ptr - offset; 
  }
  
  const char * operator *() {
    return (const char *)pgm_read_ptr_far(ptr);
  }
  
  PMPtr& operator = (const char ** ptrIn) {
     this->ptr = ptrIn;
     return *this;
  }
  
  bool operator != (const char ** ptrIn) {
     return (this->ptr != ptrIn); 
  }
  
  bool operator == (const char ** ptrIn) {
     return (this->ptr == ptrIn); 
  }
  
  bool operator > (const char ** ptrIn) {
     return (this->ptr > ptrIn); 
  }
  
  bool operator < (const char ** ptrIn) {
     return (this->ptr < ptrIn); 
  }
  
  bool operator >= (const char ** ptrIn) {
     return (this->ptr >= ptrIn); 
  }
  
  bool operator <= (const char ** ptrIn) {
     return (this->ptr <= ptrIn); 
  }
  
private:
  const char ** ptr;  
};

class Sheet {
  public:
    explicit Sheet(const char ** mainsheet, int mainsheet_len) : start(NULL), ptr(NULL), 
      fauxBegin(NULL), len(0), fauxEnd(0), repeatInstead(NULL) {
      if ( mainsheet == NULL ) {
        return;
      }
      this->newMusic(mainsheet, mainsheet_len);
    }
    
    void newMusic(const char ** mainsheet, int mainsheet_len) {
      this->start = mainsheet;
      this->ptr = this->start;
      this->fauxBegin = this->start;
      this->len = mainsheet_len;
      this->fauxEnd = this->end = this->ptr + this->len;
    }

    bool getPins(int &pin, int &time) {
      bool ret = false;
      
      time = 0;

      int note = this->getNote(time);
      //Serial.print("Note: ");
      //Serial.println(note, DEC);
      if ( note > 0 ) {
        if ( time > 0 ) {
          pin = hashPin(note);
        }
        //Serial.print("Pin: ");
        //Serial.println(pin, DEC);
        ret = true;
      }

      return ret;
    }

    int getNote(int &time) {
      const char * tptr = *this->ptr;
      int note = -1;

      if ( *tptr != '\n' ) {
        //Serial.println(*tptr);
        if ( *tptr == 'Y' ) {
          this->fauxBegin = (++this->ptr);
          return this->getNote(time);
        }
        else if ( *tptr == 'R' ) {
          if ( this->repeatCounts == 0 ) {
            this->repeatInstead = (++this->ptr);
            this->ptr = this->fauxBegin;
            ++this->repeatCounts;
            tptr = *this->ptr;
            return this->getNote(time);
          }
          else {
            ++this->ptr;
            this->repeatCounts = 0;
            return this->getNote(time);
          }
        }
        else if ( *tptr == 'Q' ) {
          if ( this->repeatCounts > 0 && this->repeatInstead != NULL ) {
            this->ptr = this->repeatInstead;
            this->repeatCounts = 0;
            tptr = *this->ptr;
          }
        }
        else if ( *tptr == 'Z' || tptr == *this->end ) {
          this->ptr = this->start;
          this->repeatCounts = 0;
          return this->getNote(time);
        }
        else if ( isalpha(*tptr) ) {
          note = *tptr;
          while (*(++tptr) != '\0' && *tptr != '\n' && isalpha(*tptr)) {
            note += *tptr;
          }
          if ( note != -1 && *tptr != '\0' && *tptr != '\n' ) {
            time = this->getNoteTime(tptr);
          }
          if ( time == 0 ) {
            note = -1;
          }
        }
      }
      //Serial.println(**this->ptr);
      ++this->ptr;

      //Serial.println(*this->ptr);
      //Serial.println(time);

      return note;
    }

    int getNoteTime(const char * tptr) {
      float ftime = 0;
      while ( !isdigit(*tptr) && *tptr != '.' && *tptr != '\0' && *tptr != '\n' && tptr != *this->end ) {
        //Serial.println("HERE4");
        tptr++;
      }
      if ( *tptr == '.' || isdigit(*tptr) ) {
        ftime = atof(tptr);
      }

      return (int)(ftime * tempo.ftime_factor);
    }

    void getNextLine() {

    }
  private:
    PMPtr start;
    PMPtr ptr;
    PMPtr repeatInstead;
    PMPtr end;

    int len;

    PMPtr fauxBegin;
    PMPtr fauxEnd;

    int repeatCounts;
};




/**** MusicQueue Class ****/

class MusicQueue {
  public:
    MusicQueue() : ready_for_load(true), load_queue(true), last_millis(0) {
      memset((this->queue), 0, no_of_pins * sizeof(int));
      memset((this->current), 0, no_of_pins * sizeof(int));
      memset((this->pwmPins), 0, no_of_pins * sizeof(unsigned char));
      memset((this->pwmCnt), 0, no_of_pins * sizeof(int));
      memset((this->pwmIndex), 0, no_of_pins * sizeof(int));
      memset((this->pwmSignals), 0, no_of_pins * sizeof(unsigned char));
    }

    ~MusicQueue() {
    }

    // ************* output *************

    void output() {
      int current_t = millis();
      int delta_t = current_t - this->last_millis;
      bool isEmpty = true;
      uint32_t outd = 0;

      bool pwm = 1;
      
      int offset = 0;

      bool readyForLoadFlag = false;
      
      int halfThrottle = pwmThrottle/2;
      
      int i = 0;
      for (; i < no_of_pins; i++) {
        
        if ( this->ready_for_load && 0 == this->current[i] ) {
          this->current[i] = this->queue[i];
          this->queue[i] = 0;

          this->pwmIndex[i] = 0;
          this->pwmCnt[i] = 0;
          this->pwmPins[i] = pwmMap[this->pwmIndex[i]];
          this->pwmSignals[i] = 0;
          //this->done[i] = false;
        }

        if ( this->current[i] > 0 ) {
          isEmpty = false;

          this->current[i] -= delta_t;
          //Serial.println(i, DEC);

          this->pwmCnt[i] = (++pwmCnt[i]) % (pwmThrottle);

          if ( 0 == this->pwmCnt[i] ) {
            ++this->pwmIndex[i];
            if ( pwmMapLen == this->pwmIndex[i] ) {
               --this->pwmIndex[i]; 
            }
            this->pwmSignals[i] = pwmMap[this->pwmIndex[i]];
          }
          else {
            this->pwmSignals[i] = ((0x01 & this->pwmSignals[i]) << 7) | (this->pwmSignals[i] >> 1);
          }
          
          isEmpty = false;
          
          pwm = 0x01 & this->pwmSignals[i];
          
          if ( 13 == i ) {
            
            Serial.print(pwmMap[this->pwmIndex[i]]);
            Serial.print("\t");
            Serial.print(this->pwmIndex[i]);
            Serial.print("\t");
            Serial.print(this->pwmSignals[i]);
            Serial.print("\t");
            Serial.println(pwm);
          }
          
          if ( pwm ) {
            outd |= (uint32_t)((uint32_t)1 << i);
          }
          else {
            outd &= ~(uint32_t)((uint32_t)1 << i);
          }

          if ( this->current[i] <= 0 ) {
            this->current[i] = 0;
            this->pwmSignals[i] = 0xff;
            readyForLoadFlag = true;
            this->pwmIndex[i] = 0;
            this->pwmCnt[i] = 0;
            //this->done[i] = true;
          }
        } // if 0
        else {
          this->pwmSignals[i] = 0;
          isEmpty &= true;
        }
      }

      if ( this->ready_for_load ) {
        this->ready_for_load = false;
        this->load_queue = true;
      }

      if ( isEmpty || readyForLoadFlag ) {
        this->ready_for_load = true;
      }

      this->last_millis = current_t;

      this->write(outd);
    }

    void addToQueue(int index, int time) {
      if ( index < no_of_pins && this->queue[index] <= 0 ) {
        this->queue[index] = time;
      }
    }

    bool IsQueueReady() {
      return load_queue;
    }
    void resetIsQueueReady() {
      this->load_queue = false;
    }
    void write(uint32_t output) {
      //digitalWrite(oe, HIGH);
      digitalWrite(strobe, LOW);
      digitalWrite(oe, LOW);

      //Serial.println(output, HEX);

      shiftOut(data, clkout, MSBFIRST, 0xFF&(output >> 16));
      shiftOut(data, clkout, MSBFIRST, 0xFF&(output >> 8));
      shiftOut(data, clkout, MSBFIRST, 0xFF&(output));

      digitalWrite(oe, HIGH);
      digitalWrite(strobe, HIGH);
    }

  private:
    int queue[no_of_pins];
    int current[no_of_pins];
    
    unsigned char pwmSignals[no_of_pins];

    unsigned char pwmPins[no_of_pins];
    
    int pwmCnt[no_of_pins];
    int pwmIndex[no_of_pins];
    bool done[no_of_pins];
    //int pwmIndexCnt;

    bool ready_for_load;
    bool load_queue;

    int last_millis;
};

/**** Instrument Class ****/

class Instrument {
  public:
    explicit Instrument(Sheet &sheetin) : sheet(sheetin)
    {}
    ~Instrument() {}
    /*
        void choose_waveshape(byte * wave, byte wvsize, int rate) {
          waveshape = wave;
          wavesize = wvsize;

          waverate = rate;
        }
    */
    void mapper() {
      int note, time;
      if ( queue.IsQueueReady() ) {
        while ( sheet.getPins(note, time) > 0 ) {
          //Serial.print("Note: ");
          //Serial.println(note, DEC);
          if ( time ) {
            this->queue.addToQueue(note, time);
          }
        }
        queue.resetIsQueueReady();
      }
    }

    void timbre() {

    }

    boolean play() {
      this->queue.output();

      //Serial.println("Next");

      return true;
    }


  private:
    uint8_t * waveshape;
    byte chord;

    byte stream_size;
    byte wavesize;
    byte waverate;

    byte wave_dt;

    int counter;

    Sheet &sheet;

    MusicQueue queue;
};

/**** Artist Class ****/

class Artist {
  public:
    Artist(Instrument &instrin) : metronome(true), last_millis(0), instr(instrin)
    {}
    ~Artist() {}

    void play_instr() {

      int curr_time = millis();

      if ( curr_time - this->last_millis >= tempo.smallest_note ) {
        metronome = true;
        this->last_millis = curr_time;
      }

      if ( metronome ) {
        this->instr.mapper();
        metronome = false;
      }

      instr.play();
    }

  private:
    const char ** m_score;

    bool metronome;
    int last_millis;

    Instrument &instr;
};

// set the 'rate' at which the note declines after initial period
//static Sheet sheet((const char **)carol_of_bells, sizeof(carol_of_bells));
//static Sheet sheet(god_rest_ye_merry_gentlemen, sizeof(god_rest_ye_merry_gentlemen));
//static Sheet sheet((const char ** )jingle_bells, sizeof(jingle_bells));
static Sheet sheet((const char **)nutcracker_march, sizeof(nutcracker_march));
static Instrument instr(sheet);
static Artist artist(instr);

void chooseCarolBells() {
  sheet.newMusic((const char **)carol_of_bells, sizeof(carol_of_bells));
  
  tempo.quarter_note = speeds[Allegro];
  tempo.thirtyTwo_note = tempo.quarter_note / 8;
  tempo.smallest_note = tempo.thirtyTwo_note;
  tempo.pwmTime = tempo.smallest_note / 4;
  tempo.ftime_factor = tempo.quarter_note;
  
  pwmThrottle = 0x10;
}

void chooseMerryGentlemen() {
  sheet.newMusic((const char **)god_rest_ye_merry_gentlemen, sizeof(god_rest_ye_merry_gentlemen));
  
  tempo.quarter_note = speeds[Moderato];
  tempo.thirtyTwo_note = tempo.quarter_note / 8;
  tempo.smallest_note = tempo.thirtyTwo_note;
  tempo.pwmTime = tempo.smallest_note / 4;
  tempo.ftime_factor = tempo.quarter_note;
  
  pwmThrottle = 0x20;
}

void chooseJingleBells() {
  sheet.newMusic((const char **)jingle_bells, sizeof(jingle_bells));
  
  tempo.quarter_note = speeds[Vivacissimo];
  tempo.thirtyTwo_note = tempo.quarter_note / 8;
  tempo.smallest_note = tempo.thirtyTwo_note;
  tempo.pwmTime = tempo.smallest_note / 4;
  tempo.ftime_factor = tempo.quarter_note;
  
  pwmThrottle = 0x40;
}

void chooseNutcrackerMarch() {
  sheet.newMusic((const char **)nutcracker_march, sizeof(nutcracker_march));
  
  tempo.quarter_note = speeds[Andante_moderato];
  tempo.thirtyTwo_note = tempo.quarter_note / 8;
  tempo.smallest_note = tempo.thirtyTwo_note;
  tempo.pwmTime = tempo.smallest_note / 4;
  tempo.ftime_factor = tempo.quarter_note;
}

void chooseRudolph() {
  sheet.newMusic((const char **)rudolph_red_nose_reindeer, sizeof(rudolph_red_nose_reindeer));
  
  tempo.quarter_note = speeds[Allegro];
  tempo.thirtyTwo_note = tempo.quarter_note / 8;
  tempo.smallest_note = tempo.thirtyTwo_note;
  tempo.pwmTime = tempo.smallest_note / 4;
  tempo.ftime_factor = tempo.quarter_note;
  
  pwmThrottle = 0x08;
}

void setup() {

  pinMode(data, OUTPUT);
  pinMode(clkout, OUTPUT);
  pinMode(strobe, OUTPUT);
  pinMode(oe, OUTPUT);
  
  digitalWrite(data, HIGH);
  digitalWrite(clkout, HIGH);
  digitalWrite(strobe, HIGH);
  digitalWrite(oe, LOW);
  
  Serial.begin(9600);

  //chooseCarolBells();
  chooseJingleBells();
  //chooseNutcrackerMarch();
  //chooseMerryGentlemen();
  //chooseRudolph();
  //reader.setScore(carol_of_bells, sizeof(carol_of_bells));
  
  //Setup soft serial for MIDI control
  mySerial.begin(31250);
  
  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 120); 
  //0xB0 is channel message, set channel volume to near max (127)
}

void loop() {
  artist.play_instr();
  
  
}

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}
