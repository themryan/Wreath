/*
 *  music.h
 *  
 *
 *  Created by Michael Ryan on 11/11/10.
 *  Copyright 2010 Griffin Enterprise. All rights reserved.
 *
 */
 
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #include <avr/pgmspace.h>
 
 #define PROGMEM_ __attribute__((section(".progmem.data")))
 
 #define SILENT_PIN        31
 
 const int mapping[][2] = {
   {'a', 14}
   , {'A', 7}
   , {('A'+'A'), 0}
   , {'b', 15}
   , {'B', 8}
   , {('B'+'B'), 1}
   , {'c', 16}
   , {'C', 9}
   , {('C'+'C'), 2}
   , {'d', 17}
   , {'D', 10}
   , {('D'+'D'), 3}
   , {'e', 18}
   , {'E', 11}
   , {('E'+'E'), 4}
   , {'f', 19}
   , {'F', 12}
   , {('F'+'F'), 5}
   , {'g', 20}
   , {'G', 13}
   , {('G'+'G'), 6}
   , {('G' + 'G' + 'G'), 0}
   , {'S', SILENT_PIN}
 };
 
 const int mappings = sizeof(mapping)/(2*sizeof(int));
 /*
Larghissimo – very, very slow (24 BPM and under)
Grave – very slow (25–45 BPM)
Lento – slowly (45–50 BPM)
Largo – broadly (50–55 BPM)
Larghetto – rather broadly (55–60 BPM)
Adagio – slow and stately (literally, "at ease") (60–72 BPM)
Adagietto – slower than andante (72–80 BPM)
Andantino – slightly slower than andante (although in some cases it can be taken to mean slightly faster than andante) (80–84 BPM)
Andante – at a walking pace (84–90 BPM)
Andante moderato – between andante and moderato (thus the name andante moderato) (90–96 BPM)
Marcia moderato – moderately, in the manner of a march[4][5] (83–85 BPM)
Moderato – moderately (96–108 BPM)
Allegro Moderato - moderately fast (108-112 BPM)
Allegretto – close to but not quite allegro (112–120 BPM)
Allegro – fast, quickly, and bright (120–168 BPM) (molto allegro is slightly faster than allegro, but always in its range)
Vivace – lively and fast (132–144 BPM)
Vivacissimo – very fast and lively (144–160 BPM)
Allegrissimo (or Allegro Vivace) – very fast (145–167 BPM)
Presto – extremely fast (168–200 BPM)
Prestissimo – even faster than Presto (200 BPM and over)
 */
 typedef enum eSpeeds {
    Larghissimo = 0, // – very, very slow (24 BPM and under)
    Grave, // – very slow (25–45 BPM)
    Lento, // – slowly (45–50 BPM)
    Largo, // – broadly (50–55 BPM)
    Larghetto, // – rather broadly (55–60 BPM)
    Adagio, // – slow and stately (literally, "at ease") (60–72 BPM)
    Adagietto, // – slower than andante (72–80 BPM)
    Andantino, // – slightly slower than andante (although in some cases it can be taken to mean slightly faster than andante) (80–84 BPM)
    Andante, // – at a walking pace (84–90 BPM)
    Andante_moderato, // – between andante and moderato (thus the name andante moderato) (90–96 BPM)
    Marcia_moderato, // – moderately, in the manner of a march[4][5] (83–85 BPM)
    Moderato, // – moderately (96–108 BPM)
    Allegro_Moderato, // - moderately fast (108-112 BPM)
    Allegretto, // – close to but not quite allegro (112–120 BPM)
    Allegro, // – fast, quickly, and bright (120–168 BPM) (molto allegro is slightly faster than allegro, but always in its range)
    Vivace, // – lively and fast (132–144 BPM)
    Vivacissimo, // – very fast and lively (144–160 BPM)
    Allegrissimo, // (or Allegro Vivace) – very fast (145–167 BPM)
    Presto, // – extremely fast (168–200 BPM)
    Prestissimo // – even faster than Presto (200 BPM and over)
 };
 
 const int speeds[] = {
   (60000)/24,
   (60000)/35,
   (60000)/47,
   (60000)/53,
   (60000)/57,
   (60000)/67,
   (60000)/76,
   (60000)/82,
   (60000)/87,
   (60000)/93,
   (60000)/84,
   (60000)/112,
   (60000)/114,
   (60000)/138, //(60*1000)/138,
   (60000)/144, //(60*1000)/144,
   (60000)/152,
   (60000)/160,
   (60000)/184,
   (60000)/200
 };
 
 
// carol of the bells
PROGMEM_ const char * const carol_of_bells[] = {
  // B flat & E flat
  
  "D3", "b$3", "d3", "\n",
  "E3", "a3", "c3", "\n",
  "F#3", "b$3", "d3", "\n",
  "D1", "\n",
  "E1", "\n",
  "F#1", "\n",
  // begin
  "Y",
  "G3", "b$1", "\n",
  "a.5", "\n",
  "b$.5", "\n",
  "G1", "\n",
  "F3", "b$1", "\n",
  "a.5", "\n",
  "b$.5", "\n",
  "G1", "\n",
  "E$3", "b$1", "\n",
  "a.5", "\n",
  "b$.5", "\n",
  "G1", "\n",
  "D3", "b$3", "d1", "\n",
  "c.5", "\n",
  "d.5", "\n",
  "b$1", "\n",
  "G3", "b$3", "d1", "\n",
  "c.5", "\n",
  "d.5", "\n",
  "b$1", "\n",
  "F3", "b$3", "d1", "\n",
  "c.5", "\n",
  "d.5", "\n",
  "b$1", "\n",
  "E$3", "b$3", "d1", "\n",
  "c.5", "\n",
  "d.5", "\n",
  "b$1", "\n",
  "D3", "b$3", "d1", "\n",
  "c.5", "\n",
  "d.5", "\n",
  "b$1", "\n",
  "GG2", "b$3", "g1", "\n",
  "g.5", "\n",
  "g.5", "\n",
  "A1", "f.5", "\n",
  "e$.5", "\n",
  "B$2", "G3", "d1", "\n",
  "d.5", "\n",
  "d.5", "\n",
  "C1", "c.5", "\n",
  "b$.5", "\n",
  "D2", "F#3", "c1", "\n",
  "c.5", "\n",
  "c.5", "\n",
  "D1", "d.5", "\n",
  "c.5", "\n",
  "GG3", "G3", "b$1", "\n",
  "a.5", "\n",
  "b$.5", "\n",
  "g1", "\n",
  "DD3", "D.5", "\n",
  "E.5", "\n",
  "F#.5", "\n",
  "G.5", "\n",
  "a.5", "\n",
  "b.5", "\n",
  "FF#2", "a2", "c.5", "\n",
  "d#.5", "\n",
  "c1", "\n",
  "GG1", "b$1", "\n",
  "DD3", "D.5", "\n",
  "E.5", "\n",
  "F#.5", "\n",
  "G.5", "\n",
  "a.5", "\n",
  "b$.5", "\n",
  "FF#2", "a2", "c.5", "\n",
  "d.5", "\n",
  "c1", "\n",
  "GG1", "b$1", "\n",
  "DD3", "b$1", "\n",
  "a.5", "\n",
  "b$.5", "\n",
  "g1", "\n",
  "EE3", "b$1", "\n",
  "a.5", "\n",
  "b$.5", "\n",
  "G1", "\n",
  "FF#3", "b$3", "d1", "\n",
  "c.5", "\n",
  "d.5", "\n",
  "b$1", "\n",
  "DD1", "b$3" ,"d1", "\n",
  "EE1", "c.5", "\n",
  "d.5", "\n",
  "FF#1", "b$1", "\n",
  "GG3", "G3", "\n",
  "R",
  // Repeat to begin
  "S1", "\n",
  "Z"
};

PROGMEM_ const char * const god_rest_ye_merry_gentlemen[] = {
  "DD1", "D1", "\n",
  "DD1", "FF1", "D1", "\n",
  "DD1", "F1", "a1", "\n",
  "CC#1", "EE1", "E1", "a1", "\n",
  "AA1", "A1", "C#1", "G1", "\n",
  "DD1", "A1", "D1", "F1", "\n",
  "AA1", "A1", "C1", "E1", "\n",
  "BB$1", "FF1", "B$1", "D1", "\n",
  "GG1", "FF1", "A1", "C1", "\n",
  "BB$1", "FF1", "D1", "\n",
  "AA1", "A1", "C#1", "E1", "\n",
  "DD1", "A1", "D1", "F1", "\n",
  "BB$1", "DD1", "D1", "G1", "\n",
  "AA2", "EE2", "C#2", "A2", "\n",
  "S1", "\n"
  "R",
  "DD1", "FF#1", "D1", "a1", "\n",
  
  "GG1", "D1", "b$1", "\n", 
  "EE1", "GG1", "C1", "G1", "\n", 
  "FF1", "C1", "G1", "\n",
  "DD1", "FF1", "F1", "b$1", "\n",
  
  "AA1", "FF1", "E$1", "c1", "\n", 
  "BB$1", "FF1", "D1", "d1", "\n", 
  "GGG1", "EE1", "C1", "a1", "\n", 
  "AA1", "EE1", "C#1", "G1", "\n", 
  
  "DD1", "FF1", "D1", "F1", "\n", 
  "DD1", "FF1", "B1", "D1", "\n", 
  "C1", "G1", "C1", "E1", "\n", 
  "A1", "C1", "F1", "\n", 
  
  "CC2", "C1", "E2", "G2", "\n", 
  "G1", "\n", 
  "DD1", "A1", "F1", "\n", 
  "EE1", "GG1", "C1", "G1", "\n", 
  
  "FF2", "C2", "a2", "\n", 
  "BB1", "FF1", "D1", "b$1", "\n", 
  "FF1", "C1", "a1", "\n", 
  
  "FFF1", "C1", "F1", "a1", "\n", 
  "GGG1", "B$1", "E1", "G1", "\n", 
  "AA1", "A1", "D1", "F1", "\n", 
  "AA1", "A1", "C$1", "E1", "\n", 
  
  "DD2", "FF2", "D2", "\n", 
  "DD2", "FF2", "D2", "\n",
  "DD.5", "FF.5", "A.5", "F.5", "\n",
  "DD.5", "FF.5", "A.5", "E.5", "\n",
  "DD1", "FF1", "B$1", "D1", "\n",
  
  "CC1", "EE1", "C2", "G2", "\n", 
  "BB$1", "GG1", "\n", 
  "AA1", "C1", "D1", "F1", "\n"
  "GGG1", "B1", "E1", "G1", "\n", 
  
  "FFF1", "A1", "F2", "a1", "\n", 
  "DD1", "FF1", "b$1", "\n",
  "AA1", "A1", "D1", "F1", "\n",
  "AA1", "A1", "C#1", "E1", "\n", 
  
  "DD2", "FF2", "D2", "\n", 
  "DD.5", "FF.5", "A.5", "F.5", "\n", 
  "DD.5", "FF.5", "A.5", "E.5", "\n", 
  "DD1", "FF1", "B1", "D1", "\n", 
  
  "CC1", "EE1", "C2", "G2", "\n", 
  "BB$1", "GG1", "\n", 
  "AA1", "A1", "D1", "F1", "\n",
  "GGG1", "B$1", "E1", "G1", "\n",
  
  "FFF1", "A1", "F2", "a1", "\n",
  "DD1", "FF1", "b$1", "\n", 
  "AA1", "C1", "F1", "c1", "\n",
  "B$1", "B1", "F1", "d1", "\n", 
  
  "FFF1", "C1", "F1", "a1", "\n",
  "GGG1", "B$1", "E1", "G1", "\n", 
  "AA1", "A1", "D1", "F1", "\n",
  "AA1", "A1", "C#1", "E1", "\n", 
  
  "DD4", "FF4", "D4", "\n",
  
  "S2", 
  
  "Z"
};

PROGMEM_ const char * const jingle_bells[] = {
  "GG1", "\n",
  "E1", "\n",
  "D1", "\n",
  "C1", "\n",
  "GG3", "\n",
  "GG.5", "\n",
  "GG.5", "\n",
  "GG1", "\n",
  "E1", "\n",
  "D1", "\n",
  "C1", "\n",
  "A3", "\n",
  "A1", "\n",
  "F1", "\n",
  "E1", "\n",
  "D1", "\n",
  "B3", "\n",
  "S1", "\n",
  "G1", "\n",
  "G1", "\n",
  "F1", "\n",
  "G1", "\n",
  "D1", "\n",
  "E3", "\n",
  "S1", "\n",
  "GG1", "\n",
  "E1", "\n",
  "D1", "\n",
  "C1", "\n",
  "GG3", "\n",
  "S1", "\n",
  "GG1", "\n",
  "E1", "\n",
  "D1", "\n",
  "C1", "\n",
  "A3", "\n",
  "A1", "\n",
  "A1", "\n",
  "F1", "\n",
  "E1", "\n",
  "D1", "\n",
  "G1", "\n",
  "G1", "\n",
  "G1", "\n",
  "G1", "\n",
  "a1", "\n",
  "G1", "\n",
  "F1", "\n",
  "D1", "\n",
  "C2", "\n",
  "B2", "G2", "\n",
  "C1", "E1", "\n",
  "C1", "E1", "\n",
  "C2", "E2", "\n",
  "C1", "E1", "\n",
  "C1", "E1", "\n",
  "C2", "E2", "\n",
  "E1", "\n",
  "G1", "\n",
  "C1.5", "\n",
  "D.5", "\n",
  "C3", "E3", "\n",
  "S1", "\n",
  "F1", "\n",
  "F1", "\n",
  "F1.5", "\n",
  "F.5", "\n",
  "F1", "\n",
  "E1", "\n",
  "E1", "\n",
  "E.5", "\n",
  "E.5", "\n",
  "E1", "\n",
  "D1", "\n",
  "D1", "\n",
  "E1", "\n",
  "D2", "\n",
  "B2", "G2", "\n",
  "C1", "E1", "\n",
  "C1", "E1", "\n",
  "C2", "E2", "\n",
  "C1", "E1", "\n",
  "C1", "E1", "\n",
  "C2", "E2", "\n",
  "E1", "\n",
  "G1", "\n",
  "C1.5", "\n",
  "D.5", "\n",
  "C3", "E3", "\n",
  "S1", "\n",
  "F1", "\n",
  "F1", "\n",
  "F1.5", "\n",
  "F.5", "\n",
  "F1", "\n",
  "E1", "\n",
  "E1", "\n",
  "E.5", "\n",
  "E.5", "\n",
  "G1", "\n",
  "G1", "\n",
  "F1", "\n",
  "D1", "\n",
  "C1", "\n",
  "S3", "\n",
  "Z"
};

PROGMEM_ const char * const nutcracker_march[] = {
  // page 1
  "G.5", "b.5", "d.5", "\n", 
  "S.5", "\n",
  "b.33", "d.33", "\n", 
  "b.33", "d.33", "\n", 
  "b.33", "d.33", "\n", 
  "E.5", "G.5", "b.5", "e.5", "\n", 
  "S.5", "\n",
  "b.5", "e.5", "\n",
  "B.5", "F#.5", "b.5", "d.5", "f#.5", "\n",
  "S.5", "\n",
  "b.5", "d.5", "\n",
  "S.5", "\n",
  "E2", "G2", "b2", "e2", "\n",
  "G.5", "b.5", "d.5", "\n",
  "S.5", "\n",
  "b.33", "d.33", "\n", 
  "b.33", "d.33", "\n", 
  "b.33", "d.33", "\n",
  "E.5", "G.5", "b.5", "e.5", "\n"
  "S.5", "\n",
  "b.5", "e.5", "\n"
  "B.5", "F#.5", "b.5", "d.5", "f#.5", "\n"
  "S.5", "\n",
  "b.5", "d.5", "\n",
  "S.5", "\n",
  "AA1", "E.525", "C.530", "S.525", "\n",
  "D.3", "S.25", "\n",
  "BB1", "c.530", "S.525", "\n", 
  "B.25", "\n", 
  "CC1", "c.530", "S.525", "\n",
  "G.25", "\n", 
  "DD1", "F#.525", "\n", 
  "D.3", "S.25", "\n", 
  "GGG1", "b.530", "S.525", "\n", 
  "c.30", "S.25", "\n",
  "AA1", "b.530", "S.525", "\n",
  "a.30", "S.25", "\n", 
  "BB1", "G.530", "S.525", "\n",
  "CC.5", "E.525", "G.3", "S.25", "\n", 
  "AA1", "F#.530", "S.525", "\n", 
  "E.30", "S.25", "\n", 
  "BB.5", "D#.530", "\n", 
  "CC#.525", "G.530", "\n",
  "DD#.25", "F#.30", "\n", 
  "EE.5", "E.525", "\n",
  "b.30", "S.25", "\n", 
  "AA.525", "C.530", "\n", 
  "BB.25", "b.30", "\n", 
  "CC.525", "a.530", "S.525", "\n", 
  "CC#.25", "G.25", "\n",
  "DD.5", "d.5", "\n",
  "S.5", "\n",
  "DD.5", "F#.5", "d.5", "S.5", "\n",
  "BB.5", "b.5", "d.5", "\n", 
  "S.5", "\n", 
  "b.33", "d.33", "\n",
  "b.33", "d.33", "\n",
  "b.33", "d.33", "\n",
  "GGG.5", "BB.5", "b.5", "d.5", "\n",
  "S.5", "\n", 
  "b.5", "e.5", "\n",
  "S.5", "\n",
  "B.5", "FF#.5", "b.5", "d.5", "f#.5", "\n",
  "S.5", "\n",
  "b.5", "d.5", "\n", 
  "S.5", "\n",
  "E2", "G2", "b2", "e2", "\n",
  "G.5", "b.5", "d.5", "\n",
  "S.5", "\n",
  "b.33", "d.33", "\n", 
  "b.33", "d.33", "\n", 
  "b.33", "d.33", "\n", 
  "E.5", "G.5", "b.33", "d.33", "\n", 
  "S.5", "\n",
  "b.5", "e.5", "\n", 
  "B.5", "F#.5", "b.5", "d.5", "f#.5", "\n",
  "S.5", 
  "b.5", "d.5", "\n",
  "S.5", "\n", 
  "E2", "G2", "b2", "e2", "\n",
  "AA1", "c.530", "S.525", "\n",
  "d.30", "S.25", "\n",
  "BB1", "c.530", "\n", 
  "b.30", "S.25", "\n",
  "CC1", "A.530", "S.525", "\n",
  "DD.5", "F#.525", "\n", 
  "a.30", "S.25", "\n",
   // page 2
   "BB1", "d.530", "S.525", "\n",
   "e.30", "S.25", "\n",
   "CC1", "d.530", "S.525", "\n",
   "c.30", "\n", 
   "DD1", "b.530", "S.525", "\n",
   "a.30", "S.25", "\n", 
   "EE.5", "G.525", "\n",
   "b.30", "S.25", "\n", 
   
   "CC.525", "e.525", "\n", 
   "BB.25", "d.25", "\n",
   "AA.5", "c.525", "\n", 
   "e.30", "S.25", "\n", 
   "DD.525", "f#.530", "\n", 
   "CC.25", "e.30", "\n",
   "BB.5", "d.525", "\n",
   
   "EE2", "g.530", "S.525", "\n", 
   "f#.30", "S.25", "\n", 
   "e.530" , "S.25", "\n", 
   "f#.30", "S.25", "\n",
   "B.5", "d#.5", "\n",
   "S.5", "\n", 
   "B.5", "d#.5", "bbb.5", "\n", 
   "S.5", "\n", 
   
   "D#2.25", "b1", "\n",
   "b.33", "\n", 
   "b.33", "\n", 
   "b.33", "\n",
   "E.5", "G.5", "\n", 
   "S.5", "\n", 
   "E.5", "\n", 
   "S.5", "\n", 
   
   "AA2", "EE2", "C.5", "\n",
   "S.5", "\n", 
   "A.5", "S.5", "\n", 
   "BB1", "DD#1", "FF#1", "\n",
   "CC#.5", "DD#.5", "\n", 
   
   "EE.5", "b2", "g2", "\n", 
   "FF#.5", "\n", 
   "GG.5", "\n",
   "GG#.5", "\n",
   "A.5", "c2", "e2", "\n",
   "B.5", "\n",
   "C.5", "\n",
   "B.5", "\n", 
   
   "A.5", "c2", "e2", "\n", 
   "GG.5", "\n", 
   "FF#.5", "\n", 
   "EE.5", "\n", 
   "DD#.5", "b2", "d#2", "f#2", "\n", 
   "CC#.5", "\n", 
   "BB.5", "\n", 
   "S.5", "\n", 
   
   "D#2", "b1", "\n", 
   "b.33", "\n", 
   "b.33", "\n", 
   "b.33", "\n", 
   "E.5", "G.5", "\n", 
   "S.5", "\n", 
   "E.5", "\n", 
   
   
   "S3", "\n", 
  "Z"
};

PROGMEM_ const char * const rudolph_red_nose_reindeer[] = {
   "G.5", "\n",
   "a1", "\n", 
   "G.5", "\n",
   "E1", "\n", 
   "c1", "\n", 
   "a1", "\n", 
   "G3", "\n", 
   "G.5", "\n", 
   "A.5", "\n",
   "G.5", "\n",
   "A.5", "\n",
   "G1", "\n",
   "c1", "\n",
   "b4", "\n",
   "F.5", "\n",
   "G1", "\n",
   "F.5", "\n",
   "D1", "\n",
   "b1", "\n",
   "a1", "\n",
   "G3", "\n",
   "Q",
   "G.5", "\n",
   "a.5", "\n",
   "G.5", "\n",
   "a.5", "\n",
   "G1", "\n",
   "A1", "\n",
   "E4", "\n",
   "R",
   "G.5", "\n",
   "a.5", "\n",
   "G.5", "\n",
   "a.5", "\n",
   "G1", "\n",
   "d1", "\n",
   "c4", "\n",
   "a1", "\n", 
   "a1", "\n", 
   "c1", "\n", 
   "a1", "\n", 
   
   "G1", "\n", 
   "E1", "\n", 
   "G2", "\n", 
   "F1", "\n", 
   "a1", "\n", 
   "G1", "\n", 
   "F1", "\n", 
   "E4", "\n", 
   "D1", "\n", 
   "E1", "\n", 
   "G1", "\n", 
   "a1", "\n", 
   "b1", "\n", 
   "b1", "\n", 
   "b2", "\n", 
   "c1", "\n", 
   "c1", "\n", 
   "b1", "\n", 
   "a1", "\n", 
   "G1", "\n", 
   "F.5", "\n", 
   "D.5", "\n", 
   "D1", "\n", 
   "S1", "\n", 
   "G.5", "\n", 
   "A1", "\n", 
   "G.5", "\n", 
   "E1", "\n", 
   "c1", "\n", 
   "a1", "\n", 
   "G3", "\n", 
   "G.5", "\n", 
   "a.5", "\n", 
   "G.5", "\n", 
   "a.5", "\n", 
   "G1", "\n", 
   "c1", "\n", 
   "b4", "\n", 
   "F.5", "\n", 
   "G1", "\n", 
   "F.5", "\n", 
   "D1", "\n", 
   "b1", "\n", 
   "a1", "\n", 
   "G3", "\n", 
   "G1", "\n", 
   "a1", "\n", 
   "G1", "\n", 
   "a1", "\n", 
   
   "G2", "\n", 
   "d2", "\n", 
   "c3", "\n", 
   
   "S4", "\n",
   
   "Z"
   
};
