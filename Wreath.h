// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Wreath_H_
#define _Wreath_H_
#include "Arduino.h"


#include "music.h"


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project Wreath here


/*
 *  Wreath.cpp
 *
 *
 *  Created by Michael Ryan on 11/11/10.
 *  Copyright 2010 Griffin Enterprise. All rights reserved.
 *
 */

#include "music.h"

// notes A, B, C, D, E, F, G

// mapping to 24 pins
// AA to 0
// A to 8
// a to 16

//extern const int mapping[2][];
extern const char * carol_of_bells[];
extern const char * god_rest_ye_merry_gentlemen[];
extern const char * jingle_bells[];
extern const int speeds[];
extern const int mappings;

const int no_of_pins = 32;
const int cycle_counts = 0x100;
/*
const int pwmMap[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
  0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05,
  0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x0B, 0x0B,
  0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0F, 0x0F, 0x10, 0x11, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2B, 0x2C,
  0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x43, 0x45, 0x47, 0x4A, 0x4C, 0x4F,
  0x51, 0x54, 0x57, 0x59, 0x5C, 0x5F, 0x62, 0x64, 0x67, 0x6A, 0x6D, 0x70, 0x73, 0x76, 0x79, 0x7C,
  0x7F, 0x82, 0x85, 0x88, 0x8B, 0x8E, 0x91, 0x94, 0x97, 0x9A, 0x9C, 0x9F, 0xA2, 0xA5, 0xA7, 0xAA,
  0xAD, 0xAF, 0xB2, 0xB4, 0xB7, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE,
  0xD0, 0xD2, 0xD3, 0xD5, 0xD7, 0xD8, 0xDA, 0xDB, 0xDD, 0xDE, 0xDF, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5,
  0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xED, 0xEE, 0xEF, 0xEF, 0xF0, 0xF1, 0xF1, 0xF2,
  0xF2, 0xF3, 0xF3, 0xF4, 0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF6, 0xF7, 0xF7, 0xF7, 0xF8, 0xF8, 0xF8,
  0xF9, 0xF9, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
  0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,
  0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF
};
*/
const int pwmThrottle = 0x08;

const int pwmMapLen = sizeof(pwmMap)/sizeof(int);

const int quarter_note = speeds[Allegro]; // speeds[Andante];
const int thirtyTwo_note = quarter_note/8;
const int smallest_note = thirtyTwo_note;
const int pwmTime = smallest_note/4;
const int ftime_factor = quarter_note;

const int pwmUnit = pwmTime/0xFF;

int data = 9;
int strobe = 8;
int clkout = 10;
int oe = 11;
int count = 0;
int dato = 0;

int guess(int in) {
 int start = in - 'A';
 if ( in >= ('a'+'a') ) {
    start = (in/2) - 'a';
 }
 else if ( in >= ('A' + 'A') ) {
   start = (in/2) - 'A';
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
 while(mapping[index][0] != hash && index < mappings) {
   //Serial.print("Find: ");
   //Serial.println(mapping[index][0], DEC);
   index++;
 }
 if ( index != 33 && index >= mappings ) {
   index = -1;
 }

 return mapping[index][1];
}


class Sheet {
 public:
   Sheet(const char ** mainsheet, int mainsheet_len) {
     this->start = mainsheet;
     this->ptr = mainsheet;
     this->fauxBegin = this->start;
     this->len = mainsheet_len;
     this->fauxEnd = this->end = this->ptr + this->len;
   }

   bool getPins(int &pin, int &time) {
     bool ret = false;
     int note = this->getNote(time);
     //Serial.print("Note: ");
     //Serial.println(note, DEC);
     if ( note > 0 ) {
       pin = hashPin(note);
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
       if ( *tptr == 'R' ) {
         if ( this->repeatCounts == 0 ) {
           this->ptr = this->fauxBegin;
           this->repeatCounts++;
           tptr = *this->ptr;
         }
         else {
           this->ptr++;
           return this->getNote(time);
         }
       }
       if ( *tptr == 'Z' || tptr == *this->end ) {
         this->ptr = this->start;
         this->repeatCounts = 0;
         return this->getNote(time);
       }
       if ( isalpha(*tptr) ) {
         note = *tptr;
         while(*(++tptr) != '\0' && *tptr != '\n' && isalpha(*tptr)) {
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
     this->ptr++;

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

     return (int)(ftime*ftime_factor);
   }

   void getNextLine() {

   }
 private:
   const char ** start;
   const char ** ptr;
   const char ** end;

   int len;

   const char ** fauxBegin;
   const char ** fauxEnd;

   int repeatCounts;
 };


/**** MusicQueue Class ****/

class MusicQueue {
  public:
    MusicQueue() : ready_for_load(true), load_queue(true), last_millis(0) {
      memset((this->queue), 0, no_of_pins*sizeof(int));
      memset((this->current), 0, no_of_pins*sizeof(int));
      memset((this->pwmPins), 0, no_of_pins*sizeof(int));
      memset((this->pwmCnt), 0, no_of_pins*sizeof(int));
      memset((this->pwmIndex), 0, no_of_pins*sizeof(int));

      //this->pwmIndexCnt = (quarter_note*3)/255;
      /*
      for(int i = 0; i < pwmMapLen; i++) {
        pwmMap[i] = (0xFF - pwmIndex)/256;
      }
      */
    }

    ~MusicQueue() {
    }

    // ************* output *************

    void output() {
     int current_t = millis();
     int delta_t = current_t - this->last_millis;
     bool isEmpty = true;
     uint32_t outd = 0;

     int mapSize = pwmMap[0];

     int pwm = 1;

     int little = 0;
     int large = 1;
     int offset = 0;

     bool readyForLoad = false;

     for(int i = 0; i < no_of_pins; i++) {
       if ( this->ready_for_load ) {
         this->current[i] = this->queue[i];
         this->queue[i] = 0;

         this->pwmIndex[i] = 0;
         this->pwmCnt[i] = 0;
         this->pwmPins[i] = pwmMap[this->pwmIndex[i]];
       }

      if ( this->current[i] > 0 ) {

        little = 0;
        large = 1;

        this->current[i] -= delta_t;

        if ( this->current[i] <= 0 ) {
		  this->current[i] = 0;
		  readyForLoad = true;
		}
        //Serial.println(i, DEC);

        mapSize = pwmMap[this->pwmIndex[i]];

        this->pwmCnt[i] = (++pwmCnt[i]) % (pwmThrottle);

        //Serial.println(pwmCnt[i], DEC);

        if ( this->pwmCnt[i] == 0 ) {
          this->pwmIndex[i] = (++this->pwmIndex[i]) % cycle_counts;

          if ( mapSize > cycle_counts/2 ) {
        	  little = 1;
        	  large = 0;

        	  this->pwmPins[i] = cycle_counts/(cycle_counts - mapSize);
          }
          else {
            this->pwmPins[i] = cycle_counts/(mapSize);
          }
        }

        if ( pwm == little ) {
           pwm = large;
        }
        else {
           pwm = (this->pwmCnt[i]<this->pwmPins[i]) ? large : little;
        }

        // < 128 ( 0 = pwmMap Counts, 1 = 256/pwmMap Counts ) && > 128 ( 0 = 256/pwmMap Counts, 1 - pwmMap Counts )

        isEmpty = false;

        outd |= ( (1 & pwm) << i );

        if ( this->ready_for_load ) {
         this->ready_for_load = false;
         this->load_queue = true;
        }
      } // if 0
      else {
       isEmpty &= true;
      }
     }
     //Serial.println(outd, BIN);
     this->write(outd);

     if ( isEmpty || readyForLoad ) {
       this->ready_for_load = true;
     }

     this->last_millis = current_t;
   }

    void addToQueue(int index, int time) {
      Serial.println("Start");
      for(int i = 0; i < no_of_pins; i++ ) Serial.println(this->queue[i]);
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
      //shiftOut(data, clkout, MSBFIRST, 0xFF&(output >> 8));
      //shiftOut(data, clkout, MSBFIRST, 0xFF&(output));

      digitalWrite(oe, HIGH);
      digitalWrite(strobe, HIGH);
    }

  private:
    int queue[no_of_pins];
    int current[no_of_pins];

    int pwmPins[no_of_pins];
    int pwmCnt[no_of_pins];
    int pwmIndex[no_of_pins];
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
          this->queue.addToQueue(note, time);
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

      if ( curr_time - this->last_millis >= smallest_note ) {
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


//Do not add code below this line
#endif /* _Wreath_H_ */
