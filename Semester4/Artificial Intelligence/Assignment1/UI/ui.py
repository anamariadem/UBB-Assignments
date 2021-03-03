from Service.service import *


class UI:
    def __init__(self):
        self._service = Service()

    def run(self):
        pygame.init()
        logo = pygame.image.load("Images/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Drone exploration")

        screen = pygame.display.set_mode((800, 400))
        screen.fill(WHITE)
        screen.blit(self._service.environment_image(), (0, 0))

        running = True


        while running:
            self._service.mark_detected_walls()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            self._service.move_dfs()
            pygame.time.delay(10)

            if self._service.is_search_finished():
                self.display_text(screen)
                pygame.time.delay(2000)
                return
            screen.blit(self._service.detected_map_image(), (400, 0))
            pygame.display.flip()

        pygame.quit()

    @staticmethod
    def display_text(screen):
        font = pygame.font.Font('Assets/Raleway-Medium.ttf', 32)
        text = font.render("Search completed", True, primary_color, secondary_color)
        text_rect = text.get_rect()
        text_rect.center = (400, 200)
        screen.fill((255, 255, 255))
        screen.blit(text, text_rect)
        pygame.display.update()
