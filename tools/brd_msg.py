#!/usr/bin/env python3
"""
Usage: python brd_msg.py <board_variant>
Example: python brd_msg.py XMC1100_Boot_Kit
"""

import sys

brd_poll_links = {
    "XMC1300_Boot_Kit": "https://github.com/Infineon/XMC-for-Arduino/discussions/367",
    "XMC1400_Arduino_Kit": "https://github.com/Infineon/XMC-for-Arduino/discussions/366",
    "XMC4200_Platform2GO": "https://github.com/Infineon/XMC-for-Arduino/discussions/364",
    "XMC4400_Platform2GO": "https://github.com/Infineon/XMC-for-Arduino/discussions/365",
    "XMC4700_Relax_Kit": "https://github.com/Infineon/XMC-for-Arduino/discussions/368"
}

deprecation_candidate_boards = [
    "XMC1300_Boot_Kit",
    "XMC4200_Platform2GO",
    "XMC4400_Platform2GO"
]

def display_brd_msg(board_name):

    if board_name in brd_poll_links:
        board_poll_link = brd_poll_links[board_name]
        
        if board_name in deprecation_candidate_boards:
     
            print("", file=sys.stderr)
            print("=" * 62, file=sys.stderr)
            print("==== === === === ===  DEPRECATION NOTICE  === === === === ====", file=sys.stderr)
            print("=" * 62, file=sys.stderr)
            print(f'The board "{board_name}" is a candidate for', file=sys.stderr)
            print('deprecation in the next major release of XMC-for-Arduino.', file=sys.stderr)
            print('Please participate in our community poll until 31-08-2025:', file=sys.stderr)
            print(f'\n{board_poll_link}\n', file=sys.stderr)
            print('And help us decide the right level of support for this board.', file=sys.stderr)
            print('Thanks a lot!', file=sys.stderr)
            print("=" * 62, file=sys.stderr)
            print("", file=sys.stderr)

        else:
        
            print("", file=sys.stderr)
            print("=" * 62, file=sys.stderr)
            print("==== === === === ===  BOARD USAGE SURVEY  === === === === ====", file=sys.stderr)
            print("=" * 62, file=sys.stderr)
            print('We would be very grateful if you could take a moment to', file=sys.stderr)
            print('participate in our community poll about the usage', file=sys.stderr)
            print(f'of the board "{board_name}".', file=sys.stderr)
            print('The poll is open until 31-08-2025:', file=sys.stderr)
            print(f'\n{board_poll_link}\n', file=sys.stderr)
            print('Your feedback is crucial to help us provide the right level', file=sys.stderr)
            print('of support for this board.', file=sys.stderr)
            print('Thanks a lot!', file=sys.stderr)
            print("=" * 62, file=sys.stderr)
            print("", file=sys.stderr)
        

def main():

    if len(sys.argv) < 2:
        print("ERROR: No board name provided!")
        return 1
    
    board_name = sys.argv[1]

    display_brd_msg(board_name)


if __name__ == "__main__":
   main()