#include <iostream>
#include <sys/time.h>
#include <tgmath.h>
#include "osm.h"
#include <cmath>
#define ZERO 0
#define EXIT_FAIL -1
#define ONE 1
#define UNROLL_LOOP 6
#define CONVERSION_SEC_TO_NANO 1000000000
#define CONVERSION_MICRO_TO_NANO 1000

/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_operation_time(unsigned int iterations){

  if( iterations == ZERO){
    return EXIT_FAIL;
  }
  double convert_time;
  int sum = ZERO;
  timeval  start_time{};
  timeval  end_time{};
  if (gettimeofday(&start_time, nullptr) == EXIT_FAIL){
    return EXIT_FAIL;
  }
  //saves calc time rounding up func
  //loop unroll - round up iterations
  unsigned int round_up =  ceil(iterations /UNROLL_LOOP);
  for(unsigned int i =ZERO; i<round_up; i++) {
    sum= sum + ONE;
    sum= sum + ONE;
    sum= sum + ONE;
    sum= sum + ONE;
    sum= sum + ONE;
    sum= sum + ONE;
  }
  gettimeofday(&end_time, nullptr);
  sum = sum+UNROLL_LOOP;
  //calc tolal time and get average per operation
  time_t calc_total_time = (CONVERSION_MICRO_TO_NANO*end_time.tv_usec +
      CONVERSION_SEC_TO_NANO*end_time.tv_sec)
  - CONVERSION_MICRO_TO_NANO*start_time.tv_usec -
  CONVERSION_SEC_TO_NANO*start_time.tv_sec;
  convert_time = (double) calc_total_time / (UNROLL_LOOP*round_up);
  return convert_time;
}

/* An empty function call with no arguments.*/
void empty_function_call(){}

/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_function_time(unsigned int iterations){
  if( iterations == ZERO){
    return EXIT_FAIL;
  }
  double converted_time;
  timeval  start_time{};
  timeval  end_time{};
  //loop unroll - round up iterations
  unsigned int round_up =  ceil(iterations /UNROLL_LOOP);
  if(gettimeofday(&start_time, nullptr)==EXIT_FAIL){
    return EXIT_FAIL;
  }
  for(unsigned int i =ZERO; i<round_up; i++) {
    empty_function_call();
    empty_function_call();
    empty_function_call();
    empty_function_call();
    empty_function_call();
    empty_function_call();
  }
  gettimeofday(&end_time, nullptr);
  //calc total time and get average per func call
  time_t calc_total_time = (CONVERSION_MICRO_TO_NANO*end_time.tv_usec +
      CONVERSION_SEC_TO_NANO*end_time.tv_sec)
      - CONVERSION_MICRO_TO_NANO*start_time.tv_usec -
      CONVERSION_SEC_TO_NANO*start_time.tv_sec;
  converted_time = (double) calc_total_time / (UNROLL_LOOP*round_up);
  return converted_time;
}
/* Time measurement function for an empty trap into the operating system.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_syscall_time(unsigned int iterations){
  if( iterations == ZERO){
    return EXIT_FAILURE;
  }
  double converted_time;
  timeval  start_time{};
  timeval  end_time{};
  //loop unroll - round up iterations
  unsigned int round_up =  ceil(iterations /UNROLL_LOOP);
  //time starts calculating at loop begin
  gettimeofday(&start_time, nullptr);
  for(unsigned int i =ZERO; i<round_up; i++) {
    OSM_NULLSYSCALL;
    OSM_NULLSYSCALL;
    OSM_NULLSYSCALL;
    OSM_NULLSYSCALL;
    OSM_NULLSYSCALL;
    OSM_NULLSYSCALL;
  }
  gettimeofday(&end_time, nullptr);
  //calc total time and get average per func call
  time_t calc_total_time = (CONVERSION_MICRO_TO_NANO*end_time.tv_usec +
      CONVERSION_SEC_TO_NANO*end_time.tv_sec)
      - CONVERSION_MICRO_TO_NANO*start_time.tv_usec -
      CONVERSION_SEC_TO_NANO*start_time.tv_sec;
  converted_time = (double) calc_total_time / (UNROLL_LOOP*round_up);
  return converted_time;
}
