#include "snake.h"

// Image
const unsigned short apple_img[400] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10A0, 0x10A0,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x29A2, 0x63C6, 0x9D87, 0x1080, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x2081, 0x5142, 0x0000, 0x5BE5, 0xA6C9, 0xBF8A, 0x4B04, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x48E2, 0x4223, 0x6628, 0x65C7, 0x2AE3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x2041, 0x79A7, 0xA1E8, 0x9166, 0x58C3, 0x2021, 0x4A83, 0x5BA5, 0x79E4, 0x68A4, 0x4082, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3882, 0xF38F, 0xFCB3, 0xFBAF, 0xFAEC, 0xFA6A, 0xE1C8, 0xC986, 0xE147,
0xF988, 0xF9C9, 0xF167, 0xA8E5, 0x1020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0xDA8B, 0xFC72, 0xF36E, 0xF2AB, 0xF2AB,
0xF26B, 0xF22A, 0xF1E9, 0xF1C8, 0xE9A8, 0xE167, 0xD926, 0xE926, 0x98A4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x40A2, 0xFB6E,
0xF36E, 0xF26A, 0xF229, 0xF209, 0xF1E9, 0xF1E9, 0xE9C8, 0xE9A8, 0xE987, 0xE947, 0xD905, 0xD0E5, 0xD0A4, 0x2020, 0x0000, 0x0000,
0x0000, 0x0000, 0x7125, 0xFB6E, 0xF2EC, 0xF22A, 0xF209, 0xF1E9, 0xF1C9, 0xF1A8, 0xE988, 0xE967, 0xE967, 0xE947, 0xD8E5, 0xC8A4,
0xC883, 0x4821, 0x0000, 0x0000, 0x0000, 0x0000, 0x8966, 0xFB2D, 0xF28B, 0xF209, 0xF1E9, 0xF1C8, 0xF1A8, 0xE988, 0xE967, 0xE947,
0xE926, 0xE926, 0xD8E5, 0xC083, 0xC863, 0x4821, 0x0000, 0x0000, 0x0000, 0x0000, 0x8125, 0xFACC, 0xF24A, 0xF1E9, 0xF1C8, 0xE9A8,
0xE988, 0xE967, 0xE947, 0xE926, 0xE906, 0xE8E6, 0xE0C5, 0xB862, 0xC042, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000, 0x50A3, 0xFA4A,
0xEA09, 0xF1C8, 0xF1A8, 0xE988, 0xE967, 0xE947, 0xE927, 0xE906, 0xE8E6, 0xE0C5, 0xC883, 0xB842, 0xA821, 0x1000, 0x0000, 0x0000,
0x0000, 0x0000, 0x1020, 0xE1C8, 0xF1C8, 0xE9A8, 0xE167, 0xE146, 0xE126, 0xE106, 0xE0E5, 0xD8C5, 0xD0A4, 0xC863, 0xB842, 0xB821,
0x8021, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x80E4, 0xF9A8, 0xD946, 0xD926, 0xD905, 0xD0E5, 0xD0C4, 0xC8A4, 0xC883,
0xC063, 0xC042, 0xB021, 0xB021, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0xC926, 0xE126, 0xD105, 0xD0E5,
0xD0C4, 0xC8A4, 0xC883, 0xC063, 0xC042, 0xB022, 0xB001, 0x8801, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x4061, 0xE906, 0xD0E5, 0xC8C4, 0xC8A4, 0xD083, 0xC863, 0xC042, 0xB021, 0xA801, 0xA801, 0x2000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7082, 0xD0C4, 0xD0A4, 0xC883, 0xA042, 0x9842, 0xB021, 0xB001, 0xA001, 0x3000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2020, 0x3821, 0x2000, 0x0000, 0x0000, 0x2800,
0x4000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const unsigned short grass_img[400] = {
0x84E5, 0x84A6, 0x9545, 0x8D05, 0x8D25, 0x8504, 0x84C5, 0x84E5, 0x8CE5, 0x84C6, 0x84E5, 0x8505, 0x84E5, 0x84E5, 0x8504, 0x8505,
0x8D45, 0x7D04, 0x7CC4, 0x8525, 0x84E5, 0x84E5, 0x8D25, 0x84E4, 0x84E5, 0x84E5, 0x8D05, 0x84E5, 0x7CE5, 0x7CE5, 0x8505, 0x8526,
0x7CE6, 0x7CC5, 0x84E5, 0x84E5, 0x8505, 0x8545, 0x8505, 0x7CE4, 0x84E5, 0x8524, 0x8504, 0x84A5, 0x84A5, 0x84E5, 0x8D25, 0x8505,
0x7CC5, 0x7CE5, 0x84E5, 0x7CC5, 0x74C5, 0x74A5, 0x7D05, 0x8505, 0x7CE5, 0x8506, 0x8D25, 0x8D05, 0x7CC5, 0x7CE4, 0x8505, 0x84C5,
0x84E5, 0x8505, 0x8505, 0x8505, 0x7CC5, 0x7CC6, 0x8506, 0x8506, 0x8506, 0x7D05, 0x7CE5, 0x7CE5, 0x8525, 0x8505, 0x8D05, 0x84E5,
0x7CE5, 0x7CE4, 0x84C5, 0x7CC4, 0x7D05, 0x7CE4, 0x7CC5, 0x8D25, 0x7D05, 0x7CC6, 0x7CE5, 0x8526, 0x8D66, 0x7CE5, 0x8505, 0x8525,
0x8505, 0x7CE4, 0x7CC5, 0x7CC5, 0x8D05, 0x8D05, 0x8525, 0x84E4, 0x84E5, 0x7CE5, 0x74A4, 0x7CC5, 0x8525, 0x8525, 0x7D05, 0x7CC5,
0x8D06, 0x8505, 0x8545, 0x7D24, 0x7CE5, 0x7CE5, 0x8505, 0x7CC5, 0x8505, 0x84E5, 0x7484, 0x9546, 0x84E4, 0x8505, 0x7CE5, 0x8D25,
0x8544, 0x7D04, 0x8525, 0x8525, 0x84E5, 0x8525, 0x8545, 0x7D44, 0x74C5, 0x8505, 0x7CE4, 0x84E5, 0x84E5, 0x84E5, 0x7CC6, 0x8D05,
0x8505, 0x8D45, 0x8525, 0x8505, 0x8524, 0x7D24, 0x8D45, 0x8D25, 0x8525, 0x8D45, 0x84E5, 0x8505, 0x7CE5, 0x7CE5, 0x7CE4, 0x7CE4,
0x84E4, 0x7CC4, 0x7CC5, 0x8D05, 0x8D05, 0x84E4, 0x8525, 0x7CE4, 0x7CC4, 0x8525, 0x8525, 0x8D45, 0x7D24, 0x8D45, 0x84E5, 0x8D26,
0x8525, 0x8526, 0x84E5, 0x7CA5, 0x84E5, 0x8504, 0x7CC5, 0x7CE5, 0x8D65, 0x7D04, 0x8525, 0x8D45, 0x7CC5, 0x7D05, 0x8504, 0x8D25,
0x84E5, 0x8505, 0x9565, 0x8505, 0x8D25, 0x8D45, 0x8D05, 0x84C5, 0x84E5, 0x8504, 0x84E4, 0x84E5, 0x8504, 0x8505, 0x8D45, 0x7D04,
0x7CC4, 0x8505, 0x84E5, 0x84C6, 0x9545, 0x8D05, 0x8D25, 0x8524, 0x84C5, 0x8504, 0x8D05, 0x84E6, 0x84E5, 0x84E4, 0x7CE4, 0x7CA5,
0x84C5, 0x8D05, 0x8505, 0x8D45, 0x8505, 0x7CE4, 0x84E5, 0x84E5, 0x8D25, 0x8504, 0x8505, 0x8505, 0x8D05, 0x84C5, 0x84E4, 0x84E5,
0x7CE5, 0x7CC5, 0x8525, 0x7CA4, 0x7CE5, 0x8525, 0x8505, 0x8505, 0x8D25, 0x8D05, 0x84E5, 0x8524, 0x8504, 0x7CE5, 0x8D25, 0x84E5,
0x7CC5, 0x84E5, 0x7CC5, 0x84E5, 0x8506, 0x7CE5, 0x7CA4, 0x7D04, 0x8505, 0x84E5, 0x84E5, 0x8D26, 0x8D25, 0x8505, 0x7CC5, 0x84E4,
0x8525, 0x7CC4, 0x8505, 0x8525, 0x8505, 0x84E5, 0x7CE5, 0x84E6, 0x7CE5, 0x84E5, 0x7CE4, 0x7CA5, 0x7CC5, 0x74A4, 0x7CE4, 0x8504,
0x7CC5, 0x7CC5, 0x7CE5, 0x7CE4, 0x8505, 0x7D04, 0x8505, 0x8D25, 0x8525, 0x7D05, 0x7D05, 0x7CC6, 0x7D05, 0x7CC5, 0x74A4, 0x74A4,
0x74C4, 0x74A4, 0x7CE4, 0x8505, 0x7CC4, 0x7CC5, 0x8D06, 0x8505, 0x84E5, 0x8D24, 0x8D25, 0x84E5, 0x8505, 0x7CC5, 0x8525, 0x8545,
0x8525, 0x8525, 0x8505, 0x74C4, 0x7483, 0x7CC4, 0x7CE4, 0x7CE5, 0x74A5, 0x84E5, 0x8525, 0x84E5, 0x84E5, 0x8D25, 0x8524, 0x7CC4,
0x7CC5, 0x7CE5, 0x8524, 0x7D04, 0x8D45, 0x8525, 0x8525, 0x8505, 0x7CE4, 0x7CC4, 0x8504, 0x7CC4, 0x7CC5, 0x7CC5, 0x8505, 0x8504,
0x7CC4, 0x7CE4, 0x8505, 0x7CC5, 0x7CC5, 0x7CC5, 0x7D05, 0x7D24, 0x8525, 0x8D45, 0x7D24, 0x8524, 0x8505, 0x84E5, 0x7CC4, 0x8505,
0x84C5, 0x7CA5, 0x8504, 0x7CE4, 0x7CE4, 0x84E4, 0x8505, 0x8505, 0x8D46, 0x7CE4, 0x7CC5, 0x8525, 0x8504, 0x8D25, 0x84E5, 0x84E5,
0x9565, 0x8505, 0x8D25, 0x8D45, 0x84E5, 0x7CA5, 0x84E4, 0x84E4, 0x74A4, 0x7CC4, 0x8D45, 0x7D04, 0x8525, 0x8D45, 0x7CC4, 0x8505
};

const unsigned short snake_head_img [400] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0881, 0x08A1, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1962, 0x4305, 0x4BA7, 0x5407, 0x64A8, 0x5C48,
0x4B86, 0x1962, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2A03, 0x64A9, 0x5C88,
0x5C68, 0x5C48, 0x64C9, 0x6D09, 0x6D29, 0x6D49, 0x3244, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0881, 0x5448, 0x5428, 0x5C28, 0x5C28, 0x5C48, 0x64C9, 0x64E9, 0x64C9, 0x64C9, 0x64E9, 0x08C1, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0020, 0x8406, 0xA589, 0x5C48, 0x5428, 0x5C48, 0x5C48, 0x64C9, 0x64E9, 0x64C9, 0x6CC9, 0xBE4A, 0x9CE7,
0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3182, 0xDE67, 0xDE26, 0xA549, 0x5428, 0x5C48, 0x5C48, 0x64C9, 0x64E9,
0x5CC9, 0xB60A, 0xFF27, 0xFF67, 0x41E2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4202, 0x52A3, 0x41E2, 0xD648, 0x5C28,
0x5C48, 0x5C48, 0x64C9, 0x64E9, 0x64C9, 0xEF49, 0x5263, 0x5AC3, 0x5282, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1080,
0x83E4, 0xACC4, 0xC5E8, 0x5428, 0x5C48, 0x5C48, 0x64C9, 0x64E9, 0x64C9, 0xDEC9, 0xB564, 0x9C84, 0x18A0, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x31E2, 0xADE8, 0x6C68, 0x5428, 0x5C48, 0x5C48, 0x64C9, 0x64E9, 0x64C9, 0x7D29, 0xBEA8, 0x4222,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x43C7, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x64C9, 0x64E9,
0x64C9, 0x6509, 0x4BE8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3AE5, 0x5C68, 0x5428,
0x5C48, 0x5428, 0x5CA9, 0x64C9, 0x64C9, 0x6D29, 0x3AA5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x1921, 0x7528, 0x5C48, 0x5428, 0x6CC8, 0x85C8, 0x6D09, 0x6D09, 0x7DA9, 0x10E1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x63E4, 0x9E68, 0x8DA7, 0x9E27, 0xB708, 0xAEC8, 0xB768, 0x7485, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0840, 0x8526, 0xA687, 0x95C7, 0xA687, 0xB748,
0xA687, 0x10A0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0880,
0x7CC5, 0x95E6, 0x9E67, 0xAEC7, 0x29C2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x5344, 0x9526, 0x2141, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0x2821, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1841, 0x3082, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x2861, 0x48C3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

const unsigned short snake_up_img[400] = {
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x48C3, 0x2861, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x3082, 0x1841, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2821, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2141, 0x9526, 0x5344, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x29C2, 0xAEC7, 0x9E67, 0x95E6, 0x7CC5,
		0x0880, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10A0, 0xA687,
		0xB748, 0xA687, 0x95C7, 0xA687, 0x8526, 0x0840, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x7485, 0xB768, 0xAEC8, 0xB708, 0x9E27, 0x8DA7, 0x9E68, 0x63E4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10E1, 0x7DA9, 0x6D09, 0x6D09, 0x85C8, 0x6CC8, 0x5428, 0x5C48, 0x7528, 0x1921, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3AA5, 0x6D29, 0x64C9, 0x64C9, 0x5CA9, 0x5428, 0x5C48,
		0x5428, 0x5C68, 0x3AE5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4BE8, 0x6509, 0x64C9,
		0x64E9, 0x64C9, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x43C7, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x4222, 0xBEA8, 0x7D29, 0x64C9, 0x64E9, 0x64C9, 0x5C48, 0x5C48, 0x5428, 0x6C68, 0xADE8, 0x31E2, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x18A0, 0x9C84, 0xB564, 0xDEC9, 0x64C9, 0x64E9, 0x64C9, 0x5C48, 0x5C48, 0x5428, 0xC5E8, 0xACC4, 0x83E4,
		0x1080, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5282, 0x5AC3, 0x5263, 0xEF49, 0x64C9, 0x64E9, 0x64C9, 0x5C48, 0x5C48,
		0x5C28, 0xD648, 0x41E2, 0x52A3, 0x4202, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41E2, 0xFF67, 0xFF27, 0xB60A, 0x5CC9,
		0x64E9, 0x64C9, 0x5C48, 0x5C48, 0x5428, 0xA549, 0xDE26, 0xDE67, 0x3182, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020,
		0x9CE7, 0xBE4A, 0x6CC9, 0x64C9, 0x64E9, 0x64C9, 0x5C48, 0x5C48, 0x5428, 0x5C48, 0xA589, 0x8406, 0x0020, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x08C1, 0x64E9, 0x64C9, 0x64C9, 0x64E9, 0x64C9, 0x5C48, 0x5C28, 0x5C28, 0x5428, 0x5448, 0x0881,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3244, 0x6D49, 0x6D29, 0x6D09, 0x64C9, 0x5C48, 0x5C68,
		0x5C88, 0x64A9, 0x2A03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1962, 0x4B86,
		0x5C48, 0x64A8, 0x5407, 0x4BA7, 0x4305, 0x1962, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x08A1, 0x0881, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
		};
const unsigned short snake_left_img[400] = {
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0860, 0x4202, 0x3182, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0040, 0x3A02, 0x83E4, 0x5AA3, 0xDE67, 0x8406,
		0x08C1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1942, 0x3AE5, 0x4BC8, 0xADC8,
		0xACC4, 0x41E2, 0xDE26, 0xA589, 0x5448, 0x2A03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0840, 0x63E4,
		0x7528, 0x5C68, 0x5448, 0x6C68, 0xC5E8, 0xD648, 0xA549, 0x5C48, 0x5428, 0x64A9, 0x1942, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0880, 0x8526, 0x9E68, 0x5C48, 0x5428, 0x5C48, 0x5428, 0x5428, 0x5C28, 0x5428, 0x5428, 0x5C28, 0x5C88, 0x3B05, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x7CC5, 0xA687, 0x8DA7, 0x5428, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48,
		0x5C28, 0x5C68, 0x4BA7, 0x0000, 0x0800, 0x2861, 0x1841, 0x1020, 0x5324, 0x95E6, 0x95C7, 0x9E27, 0x6CC8, 0x5428, 0x5C48, 0x5C48,
		0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5407, 0x0881, 0x0000, 0x48C3, 0x3082, 0x2862, 0x9526, 0x9E67, 0xA687, 0xB708,
		0x85C8, 0x5CA9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64A8, 0x08A1, 0x0000, 0x0000, 0x0000, 0x0000,
		0x2141, 0xAEC7, 0xB748, 0xAEC8, 0x6D09, 0x64C9, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x6D09, 0x5C48, 0x0020,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x29C2, 0xA687, 0xB748, 0x6D09, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x5CC9, 0x64C9,
		0x64C9, 0x6D29, 0x4B86, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10A0, 0x7485, 0x7D88, 0x6D29, 0x64E9, 0x7D29,
		0xDEC9, 0xEF49, 0xB60A, 0x64C9, 0x64E9, 0x6D49, 0x1962, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x1901, 0x3AC5, 0x4BE8, 0xC6A8, 0xBD64, 0x5263, 0xF727, 0xBE4A, 0x64E9, 0x3244, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4222, 0x9C84, 0x5AC3, 0xFF67, 0x9CE7, 0x10E2, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10A0, 0x5282, 0x41E2, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
		};

const unsigned short snake_right_img[400] = {
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x41E2, 0x5282, 0x10A0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x10E2, 0x9CE7, 0xFF67, 0x5AC3, 0x9C84, 0x4222, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3244, 0x64E9, 0xBE4A, 0xF727, 0x5263, 0xBD64, 0xC6A8, 0x4BE8, 0x3AC5, 0x1901,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1962, 0x6D49, 0x64E9, 0x64C9, 0xB60A, 0xEF49, 0xDEC9,
		0x7D29, 0x64E9, 0x6D29, 0x7D88, 0x7485, 0x10A0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4B86, 0x6D29, 0x64C9,
		0x64C9, 0x5CC9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x6D09, 0xB748, 0xA687, 0x29C2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0020, 0x5C48, 0x6D09, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x64E9, 0x64C9, 0x6D09, 0xAEC8, 0xB748, 0xAEC7, 0x2141,
		0x0000, 0x0000, 0x0000, 0x0000, 0x08A1, 0x64A8, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x64C9, 0x5CA9, 0x85C8,
		0xB708, 0xA687, 0x9E67, 0x9526, 0x2862, 0x3082, 0x48C3, 0x0000, 0x0881, 0x5407, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48,
		0x5C48, 0x5C48, 0x5428, 0x6CC8, 0x9E27, 0x95C7, 0x95E6, 0x5324, 0x1020, 0x1841, 0x2861, 0x0800, 0x0000, 0x4BA7, 0x5C68, 0x5C28,
		0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5C48, 0x5428, 0x8DA7, 0xA687, 0x7CC5, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x3B05, 0x5C88, 0x5C28, 0x5428, 0x5428, 0x5C28, 0x5428, 0x5428, 0x5C48, 0x5428, 0x5C48, 0x9E68, 0x8526, 0x0880, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1942, 0x64A9, 0x5428, 0x5C48, 0xA549, 0xD648, 0xC5E8, 0x6C68, 0x5448, 0x5C68, 0x7528,
		0x63E4, 0x0840, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2A03, 0x5448, 0xA589, 0xDE26, 0x41E2, 0xACC4,
		0xADC8, 0x4BC8, 0x3AE5, 0x1942, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x08C1,
		0x8406, 0xDE67, 0x5AA3, 0x83E4, 0x3A02, 0x0040, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3182, 0x4202, 0x0860, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
		};
//const unsigned short big_apple_img[1600]  = {
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39E2, 0x3A22, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x29A2, 0x7C67, 0xC708, 0x2121, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020,
//
//0x3A83, 0x7466, 0x9DE9, 0xC70C, 0xD7AB, 0x84E6, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0820, 0x20A1, 0x0000, 0x0000, 0x0000, 0x10A1, 0x7507, 0x9EA9, 0xA6C9, 0xAEA9, 0xAE89, 0xAEA8, 0x2181, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5183, 0xC326, 0x5983, 0x0000, 0x0020, 0x64C6, 0x8E89,
//
//0x85E8, 0x9628, 0x9628, 0xA6C8, 0x4B44, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x38E2, 0xAA85, 0x2040, 0x2203, 0x8649, 0x7DC8, 0x8608, 0x8E08, 0x8E68, 0x4BC4, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5942, 0x6102, 0x33A4, 0x65A7, 0x6547,
//
//0x6586, 0x5D66, 0x32E3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2861, 0x40A3, 0x48E3, 0x40C3, 0x2861,
//
//0x0800, 0x0000, 0x0000, 0x0820, 0x6122, 0x2C24, 0x2CE4, 0x34C4, 0x3BA4, 0x2162, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0820, 0x7145, 0xD28A, 0xFB2D, 0xFB2D, 0xFACC, 0xFA8B, 0xF26A, 0xD209, 0x9146, 0x40A2, 0x2041, 0x4901, 0x53A5, 0x6B05, 0x99E5,
//
//0xA8C4, 0xD167, 0xD9A8, 0xC987, 0xA125, 0x58A3, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1861, 0xCA29, 0xFB8F, 0xFCF4, 0xFC93, 0xFBAF, 0xF34E, 0xF2AB, 0xF24A,
//
//0xFA4A, 0xFA29, 0xF1E9, 0xE1C8, 0x9924, 0xD146, 0xD906, 0xD926, 0xE187, 0xF1C8, 0xF1C8, 0xF1A8, 0xF187, 0xF167, 0xC926, 0x4862,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0820, 0xD249,
//
//0xFB6E, 0xF4D3, 0xFCB3, 0xFBF0, 0xFB6E, 0xFB4E, 0xFB2D, 0xF2AB, 0xF24A, 0xF229, 0xE9E9, 0xE9C8, 0xE1A8, 0xE1A7, 0xE1C8, 0xE9C8,
//
//0xF1C8, 0xE9A8, 0xE9A8, 0xE987, 0xE146, 0xD926, 0xE126, 0xE926, 0x5862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8186, 0xFB0D, 0xF431, 0xFC93, 0xFBCF, 0xFB6E, 0xFB4E, 0xFB0D, 0xF30D, 0xF2ED,
//
//0xF2CC, 0xF28B, 0xF24A, 0xF22A, 0xF209, 0xF1E9, 0xF1E9, 0xF1C8, 0xE9A8, 0xE9A8, 0xE988, 0xE967, 0xD946, 0xD926, 0xD905, 0xD905,
//
//0xE105, 0x3041, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1041, 0xEA8A, 0xFB6E,
//
//0xFC72, 0xFBCF, 0xFB6E, 0xFAEC, 0xF26A, 0xF24A, 0xF24A, 0xF26A, 0xF26B, 0xF26A, 0xF24A, 0xF22A, 0xF209, 0xF1C9, 0xF1C8, 0xE9A8,
//
//0xE9A8, 0xE988, 0xE987, 0xE967, 0xD926, 0xD905, 0xD905, 0xD0E5, 0xE0E5, 0xA0A4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5904, 0xFACC, 0xF3AF, 0xFBAF, 0xFB6E, 0xFAEC, 0xF24A, 0xF24A, 0xF22A, 0xF229, 0xF209,
//
//0xF209, 0xF1E9, 0xF1E9, 0xF1E9, 0xF1C8, 0xF1A8, 0xE9A8, 0xE9A8, 0xE988, 0xE987, 0xE967, 0xE947, 0xD905, 0xD905, 0xD0E5, 0xD0E5,
//
//0xC8C4, 0xD0A4, 0x2821, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x99A7, 0xFB0D, 0xF38E,
//
//0xFB4E, 0xFB2D, 0xF26A, 0xF24A, 0xF24A, 0xF22A, 0xF209, 0xF209, 0xF1E9, 0xF1E9, 0xF1C9, 0xF1C8, 0xF1A8, 0xE9A8, 0xE9A8, 0xE988,
//
//0xE987, 0xE967, 0xE967, 0xE947, 0xD905, 0xD0E5, 0xD0E5, 0xD0C4, 0xC0A4, 0xD084, 0x6042, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xCA09, 0xFB0D, 0xF36E, 0xFB4E, 0xF2CC, 0xF24A, 0xF22A, 0xF22A, 0xF209, 0xF209, 0xF1E9,
//
//0xF1E9, 0xF1C9, 0xF1C8, 0xF1A8, 0xE9A8, 0xE9A8, 0xE988, 0xE967, 0xE967, 0xE967, 0xE947, 0xE947, 0xD8E5, 0xD0E5, 0xD0C4, 0xC8A4,
//
//0xC083, 0xD083, 0x8062, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1020, 0xE24A, 0xFB0D, 0xF34E,
//
//0xFB2D, 0xF28B, 0xF229, 0xF22A, 0xF209, 0xF209, 0xF1E9, 0xF1E9, 0xF1C9, 0xF1C8, 0xF1A8, 0xE9A8, 0xE988, 0xE987, 0xE967, 0xE967,
//
//0xE967, 0xE947, 0xE926, 0xE926, 0xD8E5, 0xD0C4, 0xD0C4, 0xC883, 0xC083, 0xC863, 0x9042, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x1841, 0xF26A, 0xFAEC, 0xF32D, 0xF2EC, 0xF24A, 0xF229, 0xF209, 0xF209, 0xF1E9, 0xF1E9, 0xF1C8,
//
//0xF1C8, 0xF1A8, 0xE9A8, 0xE988, 0xE987, 0xE967, 0xE967, 0xE967, 0xE947, 0xE927, 0xE926, 0xE926, 0xE106, 0xD0A4, 0xC8A4, 0xC083,
//
//0xB863, 0xC063, 0x9842, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2061, 0xF24A, 0xF2CC, 0xF2ED,
//
//0xF2CC, 0xF22A, 0xF209, 0xF209, 0xF1E9, 0xF1E9, 0xF1C8, 0xF1C8, 0xF1A8, 0xE9A8, 0xE988, 0xE987, 0xE967, 0xE967, 0xE947, 0xE947,
//
//0xE926, 0xE926, 0xE906, 0xE906, 0xE8E6, 0xD0C4, 0xC883, 0xC063, 0xB862, 0xC042, 0x8842, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x1841, 0xF24A, 0xFAAB, 0xF2CC, 0xF28B, 0xF209, 0xF209, 0xF1E9, 0xF1E9, 0xF1C8, 0xF1C8, 0xF1A8,
//
//0xE9A8, 0xE988, 0xE987, 0xE967, 0xE967, 0xE947, 0xE947, 0xE926, 0xE926, 0xE906, 0xE906, 0xE8E6, 0xE8E6, 0xD8C5, 0xC083, 0xB862,
//
//0xB042, 0xC042, 0x7821, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0820, 0xE209, 0xFA6A, 0xF2AB,
//
//0xF26B, 0xF209, 0xF1E9, 0xF1E9, 0xF1C8, 0xF1C8, 0xF1A8, 0xE9A8, 0xE988, 0xE987, 0xE967, 0xE967, 0xE947, 0xE947, 0xE926, 0xE926,
//
//0xE906, 0xE906, 0xE8E6, 0xE0E5, 0xE8C5, 0xD8A4, 0xC063, 0xB842, 0xB042, 0xC042, 0x5821, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xC1A8, 0xFA2A, 0xF26A, 0xF24A, 0xF1E9, 0xF1E9, 0xF1C8, 0xF1C8, 0xE9A8, 0xE9A8, 0xE988,
//
//0xE987, 0xE967, 0xE967, 0xE947, 0xE947, 0xE926, 0xE926, 0xE906, 0xE906, 0xE8E6, 0xE0E5, 0xE8C5, 0xE0C5, 0xC883, 0xB842, 0xB042,
//
//0xB022, 0xB821, 0x3000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8125, 0xFA2A, 0xEA09,
//
//0xF209, 0xF1C9, 0xF1C8, 0xF1C8, 0xF1A8, 0xE9A8, 0xE988, 0xE987, 0xE967, 0xE967, 0xE947, 0xE947, 0xE926, 0xE926, 0xE906, 0xE906,
//
//0xE8E6, 0xE8E6, 0xE8C5, 0xD8A5, 0xC883, 0xC063, 0xB842, 0xB021, 0xB021, 0xA821, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3882, 0xFA09, 0xF1E9, 0xF1C9, 0xF1C8, 0xF1C8, 0xF1A8, 0xE9A8, 0xE987, 0xE967, 0xE967,
//
//0xE967, 0xE947, 0xE947, 0xE927, 0xE926, 0xE906, 0xE906, 0xE0E6, 0xE0C5, 0xD8A4, 0xD084, 0xC063, 0xC063, 0xC042, 0xB021, 0xA821,
//
//0xB821, 0x7821, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xC187, 0xF9E9,
//
//0xE9C8, 0xF1C8, 0xE988, 0xE167, 0xE167, 0xE146, 0xD926, 0xD926, 0xD926, 0xD906, 0xD905, 0xD8E5, 0xD8E5, 0xD0C5, 0xD0A4, 0xC8A4,
//
//0xC883, 0xC083, 0xC063, 0xC063, 0xC063, 0xB042, 0xB021, 0xA821, 0xB021, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x50A3, 0xF9E9, 0xE9A8, 0xE187, 0xE167, 0xE146, 0xD946, 0xD926, 0xD926, 0xD905,
//
//0xD0E5, 0xD0E5, 0xD0C4, 0xD0C4, 0xC8A4, 0xC8A4, 0xC8A3, 0xC883, 0xC883, 0xC063, 0xC063, 0xC042, 0xB842, 0xB021, 0xA821, 0xA801,
//
//0x9801, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB946,
//
//0xF187, 0xE167, 0xE146, 0xD946, 0xD926, 0xD906, 0xD905, 0xD905, 0xD0E5, 0xD0C4, 0xD0C4, 0xD0A4, 0xC8A4, 0xC8A4, 0xC883, 0xC883,
//
//0xC063, 0xC063, 0xC042, 0xC042, 0xB021, 0xA821, 0xA801, 0xB001, 0x5000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3061, 0xE967, 0xD946, 0xD946, 0xD926, 0xD905, 0xD905, 0xD0E5, 0xD0E5,
//
//0xD0C4, 0xD0C4, 0xC8A4, 0xC8A4, 0xC883, 0xC883, 0xC883, 0xC063, 0xC063, 0xC042, 0xC042, 0xB022, 0xA821, 0xA801, 0xA801, 0x9801,
//
//0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x80C4, 0xF147, 0xD926, 0xD905, 0xD905, 0xD0E5, 0xD0E5, 0xD0C4, 0xD0C4, 0xC8A4, 0xC8A4, 0xC883, 0xC883, 0xC883, 0xC063, 0xC063,
//
//0xC042, 0xC042, 0xB822, 0xA821, 0xA801, 0xA001, 0xB001, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0xC105, 0xE106, 0xD105, 0xD0E5, 0xD0E5, 0xD0C4, 0xD0C4,
//
//0xC8A4, 0xC8A4, 0xC883, 0xC883, 0xC063, 0xC063, 0xC063, 0xC042, 0xC042, 0xB022, 0xA821, 0xA801, 0xA001, 0xB001, 0x7000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x3841, 0xE106, 0xD0E5, 0xD0E5, 0xD0C4, 0xD0C4, 0xC8A4, 0xC8A4, 0xC883, 0xC883, 0xC063, 0xC063, 0xC063, 0xC042, 0xB842,
//
//0xB021, 0xA821, 0xA801, 0xA001, 0xA801, 0x9000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7883, 0xE8E5, 0xD0C4, 0xC8C4, 0xC8A4, 0xC8A4,
//
//0xC883, 0xC883, 0xC863, 0xD063, 0xC863, 0xC042, 0xB021, 0xA821, 0xA821, 0xA001, 0xA001, 0xA801, 0x9801, 0x1800, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x7082, 0xD0C4, 0xD8A4, 0xD083, 0xD083, 0xD063, 0xC063, 0xA842, 0x7821, 0x6821, 0x9021, 0xB021, 0xB021,
//
//0xB001, 0xB001, 0xB001, 0x8800, 0x1800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2020, 0x5841, 0x7042, 0x6041,
//
//0x4821, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x3000, 0x6800, 0x8000, 0x7800, 0x4000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
//
//};
