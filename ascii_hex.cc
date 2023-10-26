/*
 * Copyright (C) 2023. Roger Doss. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <string>
#include <iostream>

using namespace std;

char int_to_ascii_hex[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f'
};

char ascii_hex_to_int(char c) 
{
    if(c >= '0' and c <= '9') {
        return c - '0';
    }
    if(c == 'a') {
        return 10;
    }
    if(c == 'b') {
        return 11;
    }
    if(c == 'c') {
        return 12;
    }
    if(c == 'd') {
        return 13;
    }
    if(c == 'e') {
        return 14;
    }
    if(c == 'f') {
        return 15;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 3) {
        cerr << "syntax:: ascii_hex -e|-d file" << endl;
        return 1;
    }

    string output_file = argv[2];

    if(!strcmp(argv[1],"-e")) {
        output_file += ".ahex";
    } else if(!strcmp(argv[1],"-d")) {
        output_file += ".decoded";
    }

    FILE *fp  = fopen(argv[2], "r");
    FILE *out = fopen(output_file.c_str(), "w");

    if(!strcmp(argv[1],"-e")) {
        char byte = 0x0;
        fseek(fp, 0x0, SEEK_END);
        size_t size = ftell(fp);
        fseek(fp, 0x0, SEEK_SET);
        while(size--) {
            byte = fgetc(fp);
            // Split into two parts.
            char tlow = (byte & 0xF);
            char thi  = ((byte >> 4) & 0xF);
            char low = int_to_ascii_hex[(byte & 0xF)];
            char hi  = int_to_ascii_hex[(byte >> 4) & 0xF];
            fputc(hi  , out);
            fputc(low , out);
        }
    } else if(!strcmp(argv[1],"-d")) {
        fseek(fp, 0x0, SEEK_END);
        size_t size = ftell(fp);
        fseek(fp, 0x0, SEEK_SET);
        size /= 2;
        while(size--) {
            char thi  = fgetc(fp);
            char tlow = fgetc(fp);
            char hi   = ascii_hex_to_int(thi);
            char low  = ascii_hex_to_int(tlow);
            // Combine into one.
            char byte = 0x0;
            byte |= (hi << 4);
            byte |= low;
            fputc(byte, out);
        }
    }

    fclose(fp);
    fclose(out);

    return 0;
}
