/*  RTMPDump
 *  Copyright (C) 2008-2009 Andrej Stepanchuk
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RTMPDump; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <endian.h>
#include <byteswap.h>
#include <stdio.h>

int big_endian() {
    int i = 1;
    char *p = (char *)&i;

    if (p[0] == 1)
        return 0;
    else
        return 1;
}


const int consti = 1;
#define is_bigendian() ( (*(char*)&consti) == 0 )
int IsBigEndian() { return( htonl(1)==1 ); }

double ReadNumber(const char *data)
{
  int i;

  double val;
  char *dPtr = (char *)&val;
  for (i=7;i>=0;i--)
  {
    *dPtr = data[i];
    dPtr++;
  }

  return val;
}

int main(int argc, char **argv)
{
	printf("Endianess: constant: %s\n", is_bigendian() ? "BIG" : "LITTLE");
	printf("Endianness: character pointer: %s\n", big_endian() ? "BIG" : "LITTLE");
	printf("Endianness: htonl: %s\n\n", IsBigEndian() ? "BIG" : "LITTLE");

	printf("Float word order: %d\n", __FLOAT_WORD_ORDER);
	printf("Byte order      : %d\n\n", __BYTE_ORDER);

	if(argc > 1) {
		char dat[256];
		double num = 0;
		
		sscanf(argv[1], "%02X%02X%02X%02X%02X%02X%02X%02X", 
			&dat[0], &dat[1], &dat[2], &dat[3], &dat[4],
			&dat[5], &dat[6], &dat[7]);
		num = ReadNumber(dat);
		printf("dat: %01X, %01X\n", dat[0], dat[1]);
		printf("Number: %lf\n", num);
	} else {
		printf("Usage: getnum data\n");
	}
	return 0;
}

