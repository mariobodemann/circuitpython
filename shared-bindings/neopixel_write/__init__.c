/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Scott Shawcroft for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/obj.h"
#include "py/mphal.h"
#include "py/runtime.h"

#include "common-hal/nativeio/types.h"

#include "shared-bindings/neopixel_write/__init__.h"

//| :mod:`neopixel_write` --- Low-level neopixel implementation
//| ===========================================================
//|
//| .. module:: neopixel_write
//|   :synopsis: Low-level neopixel implementation
//|   :platform: SAMD21
//|
//| The `neopixel_write` module contains a helper method to write out bytes in
//| the neopixel protocol.

//| .. method:: neopixel_write.neopixel_write(digitalinout, buf, is800KHz)
//|
//|   Write buf out on the given DigitalInOut.
//|
//|   :param ~nativeio.DigitalInOut gpio: the DigitalInOut to output with
//|   :param bytearray buf: The bytes to clock out. No assumption is made about color order
//|   :param bool is800KHz: True if the pixels are 800KHz, otherwise 400KHz is assumed.
//|
STATIC mp_obj_t neopixel_write_neopixel_write_(mp_obj_t digitalinout_obj, mp_obj_t buf, mp_obj_t is800k) {
    // Convert parameters into expected types.
    const nativeio_digitalinout_obj_t *digitalinout = MP_OBJ_TO_PTR(digitalinout_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf, &bufinfo, MP_BUFFER_READ);
    // Call platform's neopixel write function with provided buffer and options.
    common_hal_neopixel_write(digitalinout, (uint8_t*)bufinfo.buf, bufinfo.len,
        mp_obj_is_true(is800k));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(neopixel_write_neopixel_write_obj, neopixel_write_neopixel_write_);

STATIC const mp_rom_map_elem_t neopixel_write_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_neopixel_write) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_neopixel_write), (mp_obj_t)&neopixel_write_neopixel_write_obj },
};

STATIC MP_DEFINE_CONST_DICT(neopixel_write_module_globals, neopixel_write_module_globals_table);

const mp_obj_module_t neopixel_write_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&neopixel_write_module_globals,
};
