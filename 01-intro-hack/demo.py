# Very simple SDL demo in Go.
#
# Sorry, this is not in a great state but I had to push it out to you. There is
# a lot of error checking that I ignore and a lot of things could be
# refactored. But at least you have something to go on for Assignment 1!

import sdl
import math

width, height = 800, 600
window = None
renderer = None

music = None
texture = None
font = None
font2 = None

title = "Intro to Video Games"
twopi = 2*math.pi
radtodeg = 180/math.pi


def center(large, small):
    return large//2 - small//2


def centeredRect(largeW, largeH, smallW, smallH):
    return sdl.Rect((
        center(largeW, smallW), center(largeH, smallH),
        smallW, smallH
    ))


def tweak(t):
    return 1 + math.sin(t)*0.1


def radToDeg(r):
    return r*radtodeg


def textureSize(t):
    _, _, _, width, height = sdl.queryTexture(t)
    return width, height


def setup():
    sdl.init(sdl.INIT_VIDEO | sdl.INIT_AUDIO)
    sdl.mixer.openAudio(22050, sdl.mixer.DEFAULT_FORMAT, 2, 4096)
    sdl.ttf.init()

    global window
    window = sdl.createWindow(
        title,
        sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
        width, height,
        sdl.WINDOW_SHOWN,
    )
    global renderer
    renderer = sdl.createRenderer(
        window,
        -1,
        sdl.RENDERER_ACCELERATED,
    )


def load():
    global music
    music = sdl.mixer.loadMUS("abstract_tracking.xm")
    image = sdl.image.load("johns-hopkins-university-logo.png")
    global texture
    texture = renderer.createTextureFromSurface(image)
    global font
    font = sdl.ttf.openFont("CaesarDressing-Regular.ttf", 72)
    global font2
    font2 = sdl.ttf.openFont("CaesarDressing-Regular.ttf", 74)


def cleanup():
    if font2 is not None:
        sdl.ttf.closeFont(font2)
    if font is not None:
        sdl.ttf.closeFont(font)
    if music is not None:
        sdl.mixer.freeMusic(music)
    if renderer is not None:
        sdl.destroyRenderer(renderer)
    if window is not None:
        sdl.destroyWindow(window)
    sdl.ttf.quit()
    sdl.mixer.closeAudio()
    sdl.quit()


def run():
    running = True
    lastTime = 0
    time = 0

    text = sdl.ttf.renderUTF8_Blended(
        font, title,
        sdl.Color((255, 255, 255, 255)).cdata[0],
    )
    textex = renderer.createTextureFromSurface(text)
    shadow = sdl.ttf.renderUTF8_Blended(
        font2, title,
        sdl.Color((0, 0, 0, 255)).cdata[0],
    )
    sdl.setSurfaceAlphaMod(shadow, 128)
    shadowex = renderer.createTextureFromSurface(shadow)

    textureW, textureH = textureSize(texture)
    textureRect = centeredRect(width, height, textureW, textureH)
    shadowRect = centeredRect(width, height, shadow.w, shadow.h)
    textRect = centeredRect(width, height, text.w, text.h)

    event = sdl.Event()
    while running:
        currentTime = sdl.getTicks()
        dt = currentTime - lastTime
        time += dt/1000.0
        lastTime = currentTime

        if time > twopi:
            time -= twopi

        while sdl.pollEvent(event):
            if event.type == sdl.QUIT:
                running = False
            elif event.type == sdl.KEYUP:
                if event.key.keysym.sym in [sdl.K_q, sdl.K_ESCAPE]:
                    running = False

        sdl.renderClear(renderer)
        sdl.renderCopyEx(
            renderer, texture,
            None, textureRect,
            radToDeg(math.sin(time)),
            sdl.Point((textureRect.w//2, textureRect.h//2)),
            sdl.FLIP_NONE
        )
        sdl.renderCopy(renderer, shadowex, None, shadowRect)
        sdl.renderCopy(renderer, textex, None, textRect)
        sdl.renderPresent(renderer)

if __name__ == "__main__":
    setup()
    load()
    sdl.mixer.playMusic(music, -1)
    run()
    cleanup()
