/*
 * GPS.h
 *
 *  Created on: 2025Äê1ÔÂ18ÈÕ
 *      Author: ORRN
 */

#ifndef CODE_GPS_H_
#define CODE_GPS_H_

#define Point_MAX   29

extern double Nomal_Error;
extern int OUT_value;
extern uint8 bridge_mode;
void GPS_init(void);
void GPS_parse(void);
void GPS_show(void);
void GPS_array_get_point(void);


void Follow_track(void);
void BD_ctrl(double Angle_error);
void GO_car(void);


#endif /* CODE_GPS_H_ */
