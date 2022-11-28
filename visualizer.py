import subprocess
import time
import argparse
import sys

import contextlib
with contextlib.redirect_stdout(None):
    import pygame

width, height = 700, 700

# Read full puzzle solution from stdout
def read_states():
    p = subprocess.Popen(["./npuzzle", *sys.argv[1:]], stdout=subprocess.PIPE)
    lines = []
    while True:
        line = p.stdout.readline().decode('utf-8').split('\n')[0]
        if line.startswith("Error"):
            print(line)
            exit(0)
        if line == "unsolvable":
            print("This puzzle is unsolvable")
            exit(0)
        if line == "#END":
            break
        if line == "":
            continue
        lines.append(line)

    info = {
        'content': lines,
        'solv':    True if lines[0] == 'solvable' else False,
        'dim':     int(lines[1].split(': ')[-1]),
        'time':  float(lines[2].split(': ')[-1]),
        'space':   int(lines[3].split(': ')[-1]),
        'steps':   int(lines[4].split(': ')[-1]),
        'curr':    0,
    }

    states = []
    lines = lines[5:]
    len_lines = len(lines)
    states = [lines[i:i+info['dim']] for i in range(0, len_lines, info['dim']+1)]
    for i, state in enumerate(states):
        states[i] = [list(map(int, r.split())) for r in state]
        
    info['states'] = states
    return info


info = read_states()

# General setup
pygame.init()
pygame.display.set_caption('N-puzzle')
screen = pygame.display.set_mode((width, height))
screen.fill((255, 255, 255))
clock = pygame.time.Clock()


# Setup the puzzle surface
puzzle_surface = pygame.Surface((600+5, 600+5))


def draw_state(state):
    size = 600 / len(state)

    # Setup font
    font = pygame.font.SysFont('timesnewroman', int(size)-int(size/2))

    for r, row in enumerate(state):
        for c, col in enumerate(row):
            if col == 0:
                continue
            # Draw piece box
            rect = pygame.Rect(c*size+6, r*size+6, size-6, size-6)
            pygame.draw.rect(puzzle_surface, (255, 255, 255), rect, border_radius=5)

            # Draw piece text
            text = font.render(str(col), True, (0, 0, 0), (255, 255, 255))
            text_w = text.get_width()
            text_h = text.get_height()
            puzzle_surface.blit(text, [rect[0]+rect[2]/2 - text_w/2, rect[1]+rect[3]/2-text_h/2])

    screen.blit(puzzle_surface, (50, 50))
    time.sleep(0.5)
    puzzle_surface.fill((0, 0, 0))


def parse_args():
    parser = argparse.ArgumentParser(description="Argument parser for N-puzzle")
    parser.add_argument('--manhattan', help='Manhattan distance heuristic', action='store_true')
    parser.add_argument('--euclidean', help='Euclidian distance heuristic', action='store_true')
    parser.add_argument('--misplaced_tiles', help="Misplaced tiles heuristic", action='store_true')
    parser.add_argument('-u', help='Uniform-cost search only', action='store_true')
    parser.add_argument('-g', help='Greedy search only', action='store_true')
    parser.add_argument('filename', help='Name of the puzzle file')
    return parser.parse_args()
    

def loop():
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        if info['curr'] < info['steps']:
            pygame.display.flip()
            draw_state(info['states'][info['curr']])
        info['curr'] += 1
        pygame.display.flip()
        clock.tick(60)

if __name__ == "__main__":
    args = parse_args()
    info = read_states()
    if info['solv'] == False:
        for line in info['content']:
            print(line)
            exit(1)
    loop()
