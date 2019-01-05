#!/usr/bin/env python3

import sys
import fileinput
import random
import re
import contextlib
with contextlib.redirect_stdout(None):
    import pygame
    from pygame.locals import *

FPS = 30

#            R    G    B
DPURPLE  = ( 41,  50,  65)

BGCOLOR  = ( 31,  40,  55)

P1_COLOR = (211,143, 48)
P1_COLOR2 = (255,202, 68)
P2_COLOR = (188, 76, 39)
P2_COLOR2 = (247,101, 44)
COLOR_DEFAULT = DPURPLE

TEXTCOLOR = (116, 125, 140)
WINNING_TEXT_COLOR = (146, 155, 170)

WINDOWHEIGHT = 1200
WINDOWWIDTH = 1200

TEXTSIZE = 30

KEYDELAY = 150
KEYREPEAT = 5

NAME1_X_OFF = 100
NAME1_Y_OFF = 100

PIECE_BKG  = ( 26,  35,  50)
PIECE_VOID = DPURPLE
PIECE_FULL = ( 66,  75,  90)

NAME2_X_OFF = 100
NAME2_Y_OFF = NAME1_Y_OFF + TEXTSIZE

BOARD_OFF_X = 100
BOARD_OFF_Y = NAME2_Y_OFF + TEXTSIZE + 10

BOARD_BOUNDS = int(WINDOWHEIGHT / 1.5) - max(BOARD_OFF_Y, BOARD_OFF_X)

PIECE_OFF_X = BOARD_OFF_X + BOARD_BOUNDS
PIECE_OFF_Y = BOARD_OFF_Y

PIECE_BOUNDS = (WINDOWWIDTH - BOARD_BOUNDS - BOARD_OFF_X) / 2

FILE_PATHS = [
    "/assets/shrek.jpg",
    "/assets/EcksDeeKirbee.png",
    "/assets/ok_hand.png",
    "/assets/tfw_dicked_by_filler.ogg",
    "/assets/yeet.ogg",
    "/assets/oof.mp3"
]

FONT = "Avenir Next"

class Game:

    def __init__(self, bgcolor, p1_color, p2_color, keydelay, keyrepeat, fps, p1_name, p2_name, board_w, board_h, game_boards, game_pieces, final_scores, winner):
        pygame.init()
        pygame.font.init()
        self.game_font = pygame.font.SysFont(FONT, TEXTSIZE)
        pygame.key.set_repeat(keydelay, keyrepeat)
        pygame.display.set_caption(p1_name + ' vs ' + p2_name)
        self.DISPLAYSURF = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT), 0, 32)
        self.clock = pygame.time.Clock()
        self.bgcolor = bgcolor
        self.p1_color = p1_color
        self.p2_color = p2_color
        self.keydelay = keydelay
        self.keyrepeat = keyrepeat
        self.fps = fps
        self.p1_name = p1_name
        self.p2_name = p2_name
        self.board_w = board_w
        self.board_h = board_h
        self.game_boards = game_boards
        self.game_pieces = game_pieces
        self.board_index = 0
        self.gapsize = 1
        self.boxsize = int(BOARD_BOUNDS / ((max(board_w, board_w) + self.gapsize))) - self.gapsize
        self.piece_off_y = BOARD_OFF_Y
        self.board_max = len(self.game_boards) - 1
        self.inc = 1
        self.final_scores = final_scores
        self.winner = winner
        self.isout = 0
        self.rnum = random.randint(0, 100)
        self.counter = 0
        self.playing = False

    def events(self):
        for self.event in pygame.event.get():
            if self.event.type == QUIT:
                self.quit()
            elif self.event.type == KEYDOWN:
                if self.event.key == 113 or self.event.key == 27:
                    self.quit()
                if self.event.key == 275: # right
                    pygame.mixer.music.stop()
                    self.playing = False
                    self.board_index = min(self.board_index + self.inc, self.board_max)
                if self.event.key == 276: # left
                    pygame.mixer.music.stop()
                    self.playing = False
                    self.board_index = max(self.board_index - self.inc, 0)
                if self.event.key == 61 or self.event.key == 273: # + or up
                    self.inc += 1
                if self.event.key == 45 or self.event.key == 274: # - or down
                    self.inc = max(self.inc - 1, 1)
                if self.event.key == 114: # r
                    self.inc = 1
                if self.event.unicode == '\x03' or self.event.unicode == '\r' or self.event.unicode == '\n': # ret
                    self.inc = max(self.counter, 1)
                    self.counter = 0
                if self.event.key == 278: # home
                    pygame.mixer.music.stop()
                    self.playing = False
                    self.board_index = 0
                if self.event.key == 279: # end
                    pygame.mixer.music.stop()
                    self.playing = False
                    self.board_index = self.board_max
                if self.event.unicode in "0123456789" or self.event.unicode == '\x03' or self.event.unicode == '\r' or self.event.unicode == '\n':
                    if self.event.unicode == '0':
                        self.counter = self.counter * 10 + 0
                    if self.event.unicode == '1':
                        self.counter = self.counter * 10 + 1
                    if self.event.unicode == '2':
                        self.counter = self.counter * 10 + 2
                    if self.event.unicode == '3':
                        self.counter = self.counter * 10 + 3
                    if self.event.unicode == '4':
                        self.counter = self.counter * 10 + 4
                    if self.event.unicode == '5':
                        self.counter = self.counter * 10 + 5
                    if self.event.unicode == '6':
                        self.counter = self.counter * 10 + 6
                    if self.event.unicode == '7':
                        self.counter = self.counter * 10 + 7
                    if self.event.unicode == '8':
                        self.counter = self.counter * 10 + 8
                    if self.event.unicode == '9':
                        self.counter = self.counter * 10 + 9
                else:
                    self.counter = 0

    def quit(self):
        pygame.font.quit()
        pygame.quit()
        sys.exit()

    def show_image(self, path):
        try:
            image = pygame.image.load(sys.path[0] + path)
            image_rect = image.get_rect()
            image_rect.center = (WINDOWWIDTH / 2, WINDOWHEIGHT / 2)
            self.DISPLAYSURF.blit(image, image_rect)
        except:
            pass

    def play_sound(self, path):
        if not self.playing:
            self.playing = True
            try:
                pygame.mixer.music.load(sys.path[0] + path)
                pygame.mixer.music.play()
            except:
                pass

    def shrekt(self):
        n = self.rnum % (len(FILE_PATHS))
        filename = FILE_PATHS[n]
        image_p = re.compile(".+\.(?:jpg|png)$")
        audio_p = re.compile(".+\.(?:ogg|mp3)$")
        if image_p.match(filename):
            self.show_image(FILE_PATHS[n])
        elif audio_p.match(filename):
            textsurf = self.game_font.render(filename.split('/')[-1], True, TEXTCOLOR)
            textrect = textsurf.get_rect()
            textrect.center = (WINDOWWIDTH / 2, WINDOWHEIGHT / 2)
            self.DISPLAYSURF.blit(textsurf, textrect)
            self.play_sound(filename)

    def display_board(self):
        row = 0
        if self.game_boards[self.board_index] == []:
            self.shrekt()
            return
        for line in self.game_boards[self.board_index]:
            col = 0
            for n in line:
                if n == 'x':
                    print_color = P2_COLOR2
                elif n == 'X':
                    print_color = P2_COLOR
                elif n == 'o':
                    print_color = P1_COLOR2
                elif n == 'O':
                    print_color = P1_COLOR
                else:
                    print_color = COLOR_DEFAULT
                pygame.draw.rect(self.DISPLAYSURF, print_color, (BOARD_OFF_X + (self.gapsize + self.boxsize) * col, BOARD_OFF_Y + (self.gapsize + self.boxsize) * row, self.boxsize, self.boxsize))
                col += 1
            row += 1

    def display_piece(self):
        row = 0
        height = len(self.game_pieces[self.board_index])
        width = len(self.game_pieces[self.board_index][0])
        pygame.draw.rect(self.DISPLAYSURF, PIECE_BKG, (PIECE_OFF_X, self.piece_off_y, PIECE_BOUNDS, PIECE_BOUNDS))
        piece_size = int(PIECE_BOUNDS / (max(width, height) + self.gapsize)) - self.gapsize
        for line in self.game_pieces[self.board_index]:
            col = 0
            for n in line:
                if n == '*':
                    print_color = PIECE_FULL
                else:
                    print_color = PIECE_VOID
                pygame.draw.rect(self.DISPLAYSURF, print_color, (PIECE_OFF_X + (self.gapsize + piece_size) * col, self.piece_off_y + (self.gapsize + piece_size) * row, piece_size, piece_size))
                col += 1
            row += 1
        textsurf = self.game_font.render("Size: " + str(height) + 'x' + str(width), True, TEXTCOLOR)
        self.DISPLAYSURF.blit(textsurf, (PIECE_OFF_X, self.piece_off_y + PIECE_BOUNDS))

    def print_score(self):
        winning_font = pygame.font.SysFont(FONT, int(TEXTSIZE * 1.25))
        textsurf = winning_font.render(self.winner + " wins: " + str(self.final_scores[0]) + ' to ' + str(self.final_scores[1]), True, WINNING_TEXT_COLOR)
        self.DISPLAYSURF.blit(textsurf, (PIECE_OFF_X, self.piece_off_y + PIECE_BOUNDS + TEXTSIZE * 2))

    def draw(self):
        self.DISPLAYSURF.fill(self.bgcolor)
        textsurf = self.game_font.render("P1: " + self.p1_name, True, self.p1_color)
        self.DISPLAYSURF.blit(textsurf, (NAME1_X_OFF, NAME1_Y_OFF))
        textsurf = self.game_font.render("P2: " + self.p2_name, True, self.p2_color)
        self.DISPLAYSURF.blit(textsurf, (NAME2_X_OFF, NAME2_Y_OFF))
        self.display_piece()
        self.display_board()
        if self.board_index == self.board_max:
            self.print_score()
        pygame.display.update()

    def run(self):
        playing = True
        while playing:
            self.clock.tick(self.fps)
            self.events()
            self.draw()

def get_piece_height(line):
    i = 6
    n = 0
    while line[i] in '0123456789':
        n = n * 10 + ord(line[i]) - ord('0')
        i += 1
    return n

def strip_input(lines):
    boards = []
    pieces = []
    working_board = []
    working_piece = []
    board_p = re.compile("^\d{3}\s[.xXoO]+$")
    piece_p = re.compile("^[.*]+$")
    for n in lines:
        if n[:5] == "    0":
            continue
        elif n[:8] == "Plateau ":
            working_board = []
        elif n[:6] == "Piece ":
            if working_board == []:
                if random.randint(0, 20) == 0:
                    boards.append(working_board)
                else:
                    boards.append([l.lower() for l in boards[-1]])
            else:
                boards.append(working_board)
            working_board = []
        elif board_p.match(n):
            working_board.append(n[4::])
        elif piece_p.match(n):
            working_piece.append(n)
        else:
            if working_piece != []:
                pieces.append(working_piece)
                working_piece = []
    return boards, pieces

def winner(line1, line2):
    nbr_p = re.compile("^\d+$")
    if nbr_p.match(line1[10::]):
        score1 = int(line1[10::])
    else:
        score1 = 0
    if nbr_p.match(line2[10::]):
        score2 = int(line2[10::])
    else:
        score2 = 0
    if score2 > score1:
        return "P2", score2, score1
    return "P1", score1, score2

def main():
    if len(sys.argv) > 1:
        if sys.argv[1] == "--help":
            print("""Navigation:
right: move game forward
left: move game backward
up or +: increment number of steps forward or backward
down or -: decrement number of steps forward or backward
r: reset steps taken
home: go to beginning of game
end: go to end of game
0-9 + ret: set number of steps to some integer
escape or q: quit""")
            sys.exit()
        else:
            print("illegal option: %s" % (sys.argv[1]))
            print("usage: ./filler_vm -f maps/map00 -p1 players/abanlin.filler -p2 players/hcao.filler | ../visu.py [--help]")
            sys.exit(1)
    lines = [n.rstrip() for n in sys.stdin]
    if len(lines) < 8:
        print("Error")
        sys.exit()
    p1_name = lines[6][15:len(lines[6]) - 1].split('/')[-1]
    p2_name = lines[8][15:len(lines[8]) - 1].split('/')[-1]
    name_p = re.compile("^\w+\.filler$")
    if not name_p.match(p1_name):
        p1_name = '?'
    if not name_p.match(p2_name):
        p2_name = '?'
    game_boards, game_pieces = strip_input(lines)
    if game_boards == [] or game_pieces == []:
        print("Error")
        sys.exit()
    board_h = len(game_boards[0])
    board_w = len(game_boards[0][0])
    winning_info = winner(lines[-2], lines[-1])
    filler = Game(BGCOLOR, P1_COLOR, P2_COLOR, KEYDELAY, KEYREPEAT, FPS, p1_name, p2_name, board_w, board_h, game_boards, game_pieces, (winning_info[1], winning_info[2]), winning_info[0])
    filler.run()

if __name__ == "__main__":
    main()
