import pygame
from pygame.font import *
from Solution.constants import *

def display_text(screen):
    font = pygame.font.Font('Assets/Raleway-Medium.ttf', 32)
    text = font.render("Search completed", True, primary_color, secondary_color)
    text_rect = text.get_rect()
    text_rect.center = (400, 200)
    screen.fill((255, 255, 255))
    screen.blit(text, text_rect)
    pygame.display.update()