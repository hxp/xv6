//
//  This software includes code derived from xv6 which is
//  Copyright (c) 2006-2009 Frans Kaashoek, Robert Morris, Russ Cox,
//                        Massachusetts Institute of Technology
//
//  See LICENSE.MIT for the full licence details.
//

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

#define SEEK_SET    0   // set it to 0 + offset
#define SEEK_CUR    1   // set file offset to current plus offset 
#define SEEK_END    2   // set to end of file + offset
