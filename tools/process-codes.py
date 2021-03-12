#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import os.path
from hamster import Hamster

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Click codes gnerator')
    parser.add_argument('-s', '--start', type=int, default=0, help='Start code')
    parser.add_argument('-e', '--end', type=int, default=63, help='End code')
    args = parser.parse_args()

hamster = Hamster()

for click_code in range(args.start, args.end + 1):
    if not os.path.isfile(Hamster.motor_file_name(click_code)):
        hamster.start(click_code)

    if not os.path.isfile(Hamster.motor_file_name(click_code, reverse_code=True)):
        hamster.start(click_code, reverse_code=True)
