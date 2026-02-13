#!/usr/bin/sh
#
# if this script is not executable then do
#     chmod +x run.sh
#
# this script assumes that lab2 is in the current directory
# and there is a tests directory with the input files
#
# MP2 place in student directory
./lab2 < tests/t00testinput > gradingout_t00testinput
./lab2 < tests/t01quit_10 > gradingout_t01quit_10
./lab2 < tests/t02onereq_2 > gradingout_t02onereq_2
./lab2 < tests/t03oneadd_2 > gradingout_t03oneadd_2
./lab2 < tests/t04oneaddremove_4 > gradingout_t04oneaddremove_4
./lab2 < tests/t05oneaddrevip_4 > gradingout_t05oneaddrevip_4
./lab2 < tests/t06nineadds_9 > gradingout_t06nineadds_9
./lab2 < tests/t07addsrealloc_2 > gradingout_t07addsrealloc_2
./lab2 < tests/t08addremove_4 > gradingout_t08addremove_4
./lab2 < tests/t09duplicates_2 > gradingout_t09duplicates_2
./lab2 < tests/t10onescan_2 > gradingout_t10onescan_2
./lab2 < tests/t11scans_2 > gradingout_t11scans_2
./lab2 < tests/t12dels_8 > gradingout_t12dels_8
./lab2 < tests/t13nomatches_5 > gradingout_t13nomatches_5
./lab2 < tests/t14emptylist_10000 > gradingout_t14emptylist_10000
./lab2 < tests/t15threescan_2 > gradingout_t15threescan_2
./lab2 < tests/t16qonereq > gradingout_t16qonereq
./lab2 < tests/t17qonepop > gradingout_t17qonepop
./lab2 < tests/t18q9alerts > gradingout_t18q9alerts
./lab2 < tests/t19qdups > gradingout_t19qdups
