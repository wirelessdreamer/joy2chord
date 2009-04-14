 /***************************************************************************
 *   Copyright (C) 2007 by Nathanael Anderson                              *
 *   wirelessdreamer AT gmail DOT com                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _JOY2CHORD_H_
#define _JOY2CHORD_H_

#include <string>
#include <map>

#define TOOL_NAME "joy2chord"

using namespace std;

const int MAX_CODES = 512; // input.h can define up to 512 input buttons, so using 512 here too
const int MAX_BUTTONS = 64;// I ran into problems dynamically allocating how many array positions there would be for holding buttons, so using this for now
const int MAX_MODES = 16; // same problem with dynamically allocating
const int MAX_AXES = 64; // same problem with dynamically allocating
const int MAX_BAD = 40000; // A workaround for handling device initilization input, This should only be a Temp Solution
const int MAX_MACROS = 16; // How many macros can be understood
const int MAX_MODIFIERS = 8; // How many modifier codes can be used (ctrl, alt, meta, etc) these keys are held down untill a non modifier is held down

static int uinp_fd = -1;
struct uinput_user_dev uinp;       // uInput device structure
struct input_event event; // Input device structure

class joy2chord
{
public:
	string device_name;
	string config_file;

	// mapping variables
	__u16 modes[MAX_MODES][MAX_CODES];
	__u16 simple_modes[MAX_MODES][MAX_CODES];
	__u16 modifier[MAX_MODIFIERS];
	int total_modifiers;
	int modifier_state[MAX_MODIFIERS];
	int total_modes;
	int mode_code[MAX_MODES];
	int total_macros;
	int macro_values[MAX_MACROS];
	int mode;
	int button_state[MAX_BUTTONS];
	int send_code[MAX_BUTTONS];
	int modecount[MAX_MODES];
	int button_code;
	int verbose;
	int debug;
	int calibration;
	int quickpress;
	int readytosend;
	
	// joystick variables
	int device_number; 
	int total_chorded_buttons; // how many buttons are treated as a chorded keyboard
	int total_simple_buttons; // how many buttons are treated as a normal key
	int controller_buttons; // how many buttons the hardware controller provides
	int axes; // how many axes we defined functions for
	int total_axes; // how many analog axes the hardware controller provides
	int chord_values[MAX_CODES];
	int simple_values[MAX_CODES];
	int joy_fd;
	__u16 lastkey;
	__u16 thiskey;
	int justpressed;

	int open_joystick();
	int setup_uinput_device();
	int read_config(map<string, __u16> & chordmap);
	void send_click_events();
	void send_key_down(__u16 key_code);
	void send_key_up(__u16 key_code);
	void process_events(js_event js);
	int valid_key(string newkey);
	void main_loop(map<string, __u16> chordmap);
	void ioctl_wrapper(int uinp_fd, int UI_SETBIT, int i);
	void macro_parser(string macro);
	void write_uinput();
};

#endif
