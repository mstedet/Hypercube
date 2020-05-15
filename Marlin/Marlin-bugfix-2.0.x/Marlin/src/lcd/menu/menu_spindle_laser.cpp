/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//
// Spindle / Laser Menu
//

#include "../../inc/MarlinConfig.h"

#if HAS_LCD_MENU && HAS_CUTTER

  #include "menu.h"

  #include "../../feature/spindle_laser.h"

  void menu_spindle_laser() {

    const bool can_disable = cutter.enabled() && cutter.isOn;

    START_MENU();
    BACK_ITEM(MSG_MAIN);

    #if ENABLED(SPINDLE_LASER_PWM)
      EDIT_ITEM_FAST( CUTTER_MENU_POWER_TYPE, MSG_CUTTER(POWER), &cutter.setPower
                    , cutter.interpret_power(SPEED_POWER_MIN), cutter.interpret_power(SPEED_POWER_MAX)
                    , []{ if (cutter.isOn) cutter.power = cutter.setPower; }
      );
    #endif

    if (can_disable)
      ACTION_ITEM(MSG_CUTTER(OFF), cutter.disable);
    else {
      ACTION_ITEM(MSG_CUTTER(ON), cutter.enable_forward);
      #if ENABLED(SPINDLE_CHANGE_DIR)
        ACTION_ITEM(MSG_SPINDLE_REVERSE, cutter.enable_reverse);
      #endif
    }

    #if ENABLED(MARLIN_DEV_MODE)
      #if ENABLED(HAL_CAN_SET_PWM_FREQ) && defined(SPINDLE_LASER_FREQUENCY)
        EDIT_ITEM_FAST(CUTTER_MENU_FREQUENCY_TYPE, MSG_CUTTER_FREQUENCY, &cutter.frequency, 2000, 50000,[]{ cutter.refresh_frequency();});
      #endif
    #endif
    END_MENU();
  }

#endif // HAS_LCD_MENU && HAS_CUTTER
